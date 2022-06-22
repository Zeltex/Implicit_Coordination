#include "Planner.hpp"
#include "Node_Comparator.hpp"
#include "Memory.hpp"
#include "Domain.hpp"
#include "Planner_Debug_Info.hpp"

#include <assert.h>

namespace del {

	// TODO - Node references may become invalid if more nodes are added to graph (du to vector reallocation), make sure this is not the case.

	// TODO - Check if we need to verify assumptions on initial state

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(Domain& domain, 
								Agent planning_agent,
								const bool is_benchmark) const {
		const Formula& goal_formula = domain.get_goal();
		Action_Library& action_library = domain.get_action_library();

		const State& initial_state = domain.get_current_state();
		constexpr size_t initial_node_size = 10000;
		Node_Comparator history;
		Graph graph(initial_node_size, initial_state, history, planning_agent);
		Debug_Info debug_info(domain, graph);

		// TODO - Need to check if states in initial frontier are solved
		while (!graph.is_frontier_empty()) 
		{
			debug_info.print_all();
			
			Node* current_node = graph.get_next_from_frontier();
			debug_info.print_single(current_node);
			const State& current_state = current_node->get_state();
			action_library.load_actions(current_state, domain);
			std::vector<State> perspective_shifts = current_state.get_all_perspective_shifts(domain.get_agents().size());

			while (action_library.has_action()) 
			{
				const Action& action = action_library.get_next_action();
				assert(action.get_owner().id < perspective_shifts.size());
				std::optional<State> temp_state = perspective_shifts.at(action.get_owner().id).product_update(action, domain);
				if (!temp_state.has_value())
				{
					continue;
				}

				State state_product_update = temp_state.value().contract();

				Node* child_node = history.does_bisimilar_exist_and(graph, state_product_update);
				if (child_node != nullptr)
				{
					graph.set_parent_child(current_node, child_node, action);
					continue;
				}
			
				Node* action_node = graph.create_and_node(state_product_update, current_node, action);
				debug_info.print_single(action_node);
				history.insert(action_node);
				debug_info.update_and(state_product_update);


				for (State& global_state : state_product_update.split_into_globals()) 
				{
					global_state.remove_unreachable_worlds();
					global_state = global_state.contract();

					Node* child_node = history.does_bisimilar_exist_or(graph, global_state);
					if (child_node != nullptr)
					{
						graph.set_parent_child(action_node, child_node, action);
						continue;
					}

					debug_info.update_or(global_state);
					Node* global_agent_node = graph.create_or_node(global_state, action_node);
					if (global_agent_node->is_goal(goal_formula, domain)) 
					{
						global_agent_node->set_solved();
					} 
					else 
					{
						graph.add_to_frontier(global_agent_node);
					}
					history.insert(global_agent_node);
				}
				check_node(action_node, false);
			}
			check_node(current_node);
			auto policy = check_root(graph, is_benchmark);
			if (policy.has_value()) 
			{
				debug_info.print_final();
				return policy.value();
			}
		}
		debug_info.print_final();
		std::cout << "No policy found\n";
		return Policy(false);
	}

	std::optional<Policy> Planner::check_root(Graph& graph, const bool is_benchmark) const 
	{
		if (graph.get_root_node()->is_dead()) 
		{
			std::cout << "No policy found\n";
			return Policy(false);
		}
		
		if (graph.get_root_node()->is_solved()) {
			std::cout << "Policy found\n";
			std::cout << "is benchmark " << is_benchmark <<  std::endl;
			if (is_benchmark) {
				return Policy(true);
			} else {
				return extract_policy(graph);
			}
		}
		return {};
	}

	void Planner::check_node(Node* node, bool check_dead) const 
	{
		if (check_dead && node->check_if_dead()) 
		{
			propogate_dead_end_node(node);
		} 
		else if (node->check_if_solved()) 
		{
			propogate_solved_node(node);
		}
	}

	Policy Planner::extract_policy(Graph& graph) const
	{
		auto best_value = calculate_best_value(graph);
		return calculate_policy(graph, best_value);
	}

	Policy Planner::calculate_policy(Graph& graph, const std::unordered_map<const Node*, size_t>& best_value) const
	{
		std::deque<Node*> frontier = { graph.get_root_node() };
		std::unordered_set<Node*> visited_or = { graph.get_root_node() };
		std::unordered_set<Node*> visited_and;

		Policy policy(true);

		while (!frontier.empty()) 
		{
			auto node = frontier.front();
			frontier.pop_front();

			if (node->get_type() == Node_Type::And) 
			{
				for (auto& child : node->get_children()) 
				{
					if (!child->is_solved())
					{
						continue;
					}

					if (visited_or.find(child) != visited_or.end())
					{
						continue;
					}

					visited_or.insert(child);
					frontier.push_back(child);
				}
			} 
			else 
			{
				size_t lowest_value = (size_t)-1;
				Node* lowest_node = nullptr;
				bool found_node = false;
				for (auto& child : node->get_children()) 
				{
					if (!child->is_solved())
					{
						continue;
					}

					if (best_value.at(child) < lowest_value) 
					{
						lowest_value = best_value.at(child);
						lowest_node = child;
						found_node = true;
					}

					if (visited_and.find(child) != visited_and.end())
					{
						continue;
					}
				}

				if (found_node) 
				{
					visited_and.insert(lowest_node);
					frontier.push_back(lowest_node);
					const auto& entry_state = node->get_state();
					const auto& entry_action = lowest_node->get_parent_action(node);
					add_policy_entry(policy, entry_state, entry_action, lowest_node);
				}
			}
		}
		return policy;
	}

	void Planner::add_policy_entry(Policy& policy, const State& state, const Action& action, const Node* node) const 
	{
		State perspective_shifted = state;
		perspective_shifted.shift_perspective(action.get_owner());

		std::vector<State> shifted_states = perspective_shifted.split_into_globals();
		for (State& shifted_state : shifted_states) {
			shifted_state.shift_perspective(action.get_owner());
			shifted_state = shifted_state.contract();
			policy.add_entry(shifted_state, action, node);
		}
	}

	std::unordered_map<const Node*, size_t> Planner::calculate_best_value(Graph& graph) const 
	{
		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(graph.get_nodes().size());
		std::priority_queue < Node_Entry, std::vector<Node_Entry>, Node_Entry_Comparator> frontier(Node_Entry_Comparator(), frontier_reserve);
		std::unordered_map<const Node*, size_t> best_value;
		std::unordered_map<const Node*, size_t> children_visited;

		// TODO - Could add these by top down traversal to avoid adding unreachable leafs
		// This would also allow to only add an or-node to frontier when all its children have been visited
		for (const Node* node : graph.get_nodes()) 
		{
			if (node->get_children().empty()) 
			{
				frontier.push({ node, 0 });
				best_value.insert({ node, 0 });
			}
		}

		while (!frontier.empty()) 
		{
			auto& [node, node_cost] = frontier.top();
			frontier.pop();

			if (node->is_root_node())
			{
				continue;
			}

			for (auto& [parent, action] : node->get_parents()) 
			{
				if (!parent->is_solved())
				{
					continue;
				}

				++children_visited[parent];
				
				if (parent->get_type() == Node_Type::Or) 
				{
					size_t new_node_cost = node_cost + action.get_cost();
					if (best_value.find(parent) == best_value.end()) 
					{
						best_value.insert({ parent, new_node_cost });
						frontier.push({ parent, new_node_cost });
					} 
					else if (new_node_cost < best_value.at(parent)) 
					{
						best_value[parent] = new_node_cost;
						frontier.push({ parent, new_node_cost });
						std::cerr << "Found node with better value in incorrect order " << node->get_id().id << " " << new_node_cost << std::endl;
					}
				} 
				else 
				{
					if (best_value.find(parent) == best_value.end()) 
					{
						best_value.insert({ parent, node_cost });
					} 
					else if (node_cost > best_value.at(parent)) 
					{
						best_value[parent] = node_cost;
					}

					if (children_visited.at(parent) == parent->get_children().size()) 
					{
						frontier.push({ parent, best_value[parent] });
					}
				}
			}
		}
		return best_value;
	}
	

	void Planner::propogate_dead_end_node(Node* node) const
	{
		node->set_dead();
		if (node->is_root_node()) 
		{
			return;
		}

		std::deque<Node*> frontier;
		std::unordered_set<Node*> visited;
		
		for (const auto& [parent_node, parent_action] : node->get_parents())
		{
			frontier.push_back(parent_node);
			visited.insert(parent_node);
		}

		Node* current_node;
		while (!frontier.empty()) 
		{
			current_node = frontier.front();
			frontier.pop_front();

			if (current_node->check_if_dead()) 
			{
				if (current_node->is_root_node()) 
				{
					return;
				}
				
				for (auto& parent : current_node->get_parents())
				{
					if (visited.find(parent.first) == visited.end()) 
					{
						frontier.push_back(parent.first);
						visited.insert(parent.first);
					}
				}
			}
		}
	}



	void Planner::propogate_solved_node(Node* node) const
	{
		node->set_solved();
		
		if (node->is_root_node())
		{
			return;
		}

		std::deque<Node*> frontier;
		std::unordered_set<Node*> visited;
		for (auto& [parent_node, parent_action] : node->get_parents())
		{
			frontier.push_back(parent_node);
			visited.insert(parent_node);
		}


		Node* current_node;
		while (!frontier.empty()) 
		{
			current_node = frontier.front();
			frontier.pop_front();
			if (current_node->check_if_solved()) 
			{
				if (current_node->is_root_node()) 
				{
					return;
				}
				
				for (auto& parent : current_node->get_parents())
				{
					if (visited.find(parent.first) == visited.end()) 
					{
						frontier.push_back(parent.first);
						visited.insert(parent.first);
					}
				}
			}
		}
	}
}
