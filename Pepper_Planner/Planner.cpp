#include "Planner.hpp"
#include "Node_Comparator.hpp"
#include "Memory.hpp"

#include <chrono>

namespace del {

	class Debug_Info
	{
	public:
		Debug_Info(const Domain& domain)
			: or_layer_size(1), and_layer_size(1), domain(&domain)
		{ }

		void print_final() const
		{
			#if DEBUG_PRINT == 1
				report_memory_usage();
				print_debug_layer();
			#endif
		}

		void print_all() const
		{
			#if DEBUG_PRINT == 1 && PRINT_PARTIAL == 0
				print_debug_layer();
			#endif
		}

		void print_single(const Node& node) const 
		{
			#if DEBUG_PRINT == 1 && PRINT_NODES == 1
				std::cout << "\nNode " << node.id << " at depth " << action_node.get_cost() << "\n";
				std::cout << node.to_string(domain) << std::endl;;
			#endif
		}

		void print_single(const Node_Id& node) const
		{
			print_single(graph->get_node(node));
		}

		void update_and(const State& state)
		{
			#if DEBUG_PRINT == 1
				const size_t cost = state.get_cost() / 100;
				if (and_layer_size.size() <= cost) {
					and_layer_size.push_back(0);
				}
				and_layer_size[cost] ++;
			#endif
		}

		void update_or(const State& state)
		{
			#if DEBUG_PRINT == 1 ||1
				const size_t cost = state.get_cost() / 100;
				if (or_layer_size.size() <= cost) {
					or_layer_size.push_back(0);
				}
				or_layer_size[cost] ++;
			#endif
		}

	private:

		void print_debug_layer() const 
		{
			std::string debug_print;
			size_t total_or_nodes = 0;
			size_t total_and_nodes = 0;
			for (size_t i = 0; i < or_layer_size.size(); ++i) 
			{
				debug_print += std::to_string(i) + "(" + std::to_string(and_layer_size.at(i)) + ", " + std::to_string(or_layer_size.at(i)) + ") ";
				total_and_nodes += and_layer_size.at(i);
				total_or_nodes += or_layer_size.at(i);
			}
			std::cout << debug_print << "\nOr:" << total_or_nodes << ", and: " << total_and_nodes << std::endl;
		}

		std::vector<size_t> or_layer_size;
		std::vector<size_t> and_layer_size;
		const Domain* domain;
		const Graph* graph;

	};

	// TODO - Node references may become invalid if more nodes are added to graph (du to vector reallocation), make sure this is not the case.

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(const Formula& goal_formula, 
								Action_Library& action_library, 
								const State& initial_state, 
								const std::vector<Agent>& agents, 
								const Domain& domain, 
								Agent_Id planning_agent,
								const bool is_benchmark) const {
		constexpr size_t initial_node_size = 10000;
		Node_Comparator history;
		Graph graph(initial_node_size, initial_state, history, planning_agent);
		Debug_Info debug_info(domain);

		// TODO - Need to check if states in initial frontier are solved
		while (!graph.is_frontier_empty()) 
		{
			debug_info.print_all();
			
			Node_Id current_node = graph.get_next_from_frontier();
			debug_info.print_single(current_node);
			const State& current_state = graph.get_node(current_node).get_state();
			action_library.load_actions(current_state, domain);
			std::vector<State> perspective_shifts = current_state.get_all_perspective_shifts(domain.get_agents().size());

			while (action_library.has_action()) 
			{
				const Action& action = action_library.get_next_action();
				std::optional<State> temp_state = perspective_shifts.at(action.get_owner().id).product_update(action, domain);
				if (!temp_state.has_value())
				{
					continue;
				}

				State state_product_update = temp_state.value().contract();

				auto [bisim_exists, child_node_id] = history.does_bisimilar_exist_and(graph, state_product_update);
				if (child_node_id.has_value())
				{
					graph.set_parent_child(current_node, child_node_id.value(), action);
				}
			
				if (bisim_exists)
				{
					continue;
				}

				Node& action_node = graph.create_and_node(state_product_update, current_node, action);
				debug_info.print_single(action_node);
				history.insert(action_node);
				debug_info.update_and(state_product_update);


				for (State& global_state : state_product_update.split_into_globals()) 
				{
					global_state.remove_unreachable_worlds();
					global_state = global_state.contract();

					auto [bisim_exists, child_node_id] = history.does_bisimilar_exist_or(graph, global_state);
					if (child_node_id.has_value())
					{
						graph.set_parent_child(action_node, child_node_id.value(), action);
					}

					if (bisim_exists)
					{
						continue;
					}

					debug_info.update_or(global_state);
					Node& global_agent_node = graph.create_or_node(global_state, action_node);
					if (global_agent_node.is_goal(goal_formula, domain)) 
					{
						global_agent_node.set_solved();
					} 
					else 
					{
						graph.add_to_frontier(global_agent_node);
					}
					history.insert(global_agent_node);
				}
				check_node(graph, action_node, false);
			}
			check_node(graph, current_node);
			auto policy = check_root(graph, domain, is_benchmark);
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

	std::optional<Policy> Planner::check_root(Graph& graph, const Domain& domain, const bool is_benchmark) const 
	{
		if (graph.get_root_node().is_dead()) 
		{
			std::cout << "No policy found\n";
			return Policy(false);
		}
		
		if (graph.get_root_node().is_solved()) {
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

	void Planner::check_node(Graph& graph, Node& node, bool check_dead) const 
	{
		if (check_dead && node.check_if_dead(graph)) 
		{
			propogate_dead_end_node(graph, node);
		} 
		else if (node.check_if_solved(graph)) 
		{
			propogate_solved_node(graph, node);
		}
	}

	void Planner::check_node(Graph& graph, Node_Id node_id, bool check_dead) const
	{
		check_node(graph, graph.get_node(node_id), check_dead);
	}

	Policy Planner::extract_policy(Graph& graph) const 
	{
		auto best_value = calculate_best_value(graph);
		return calculate_policy(graph, best_value);
	}

	Policy Planner::calculate_policy(Graph& graph, const std::unordered_map<size_t, size_t>& best_value) const
	{
		std::deque<Node_Id> frontier = { graph.get_root_node().get_id() };
		std::unordered_set<size_t> visited_or = { graph.get_root_node().get_id().id };
		std::unordered_set<size_t> visited_and;

		Policy policy(true);

		while (!frontier.empty()) 
		{
			auto node_id = frontier.front();
			frontier.pop_front();
			auto& node = graph.get_node(node_id);

			if (node.get_type() == Node_Type::And) 
			{
				for (auto& child : node.get_children()) 
				{
					if (!graph.get_node(child).is_solved())
					{
						continue;
					}

					if (visited_or.find(child.id) != visited_or.end())
					{
						continue;
					}

					visited_or.insert(child.id);
					frontier.push_back(child);
				}
			} 
			else 
			{
				size_t lowest_value = (size_t)-1;
				Node_Id lowest_node = { 0 };
				bool found_node = false;
				for (auto& child : node.get_children()) 
				{
					if (!graph.get_node(child).is_solved())
					{
						continue;
					}

					if (best_value.at(child.id) < lowest_value) 
					{
						lowest_value = best_value.at(child.id);
						lowest_node = child;
						found_node = true;
					}

					if (visited_and.find(child.id) != visited_and.end())
					{
						continue;
					}
				}

				if (found_node) 
				{
					visited_and.insert(lowest_node.id);
					frontier.push_back(lowest_node);
					const auto& entry_state = graph.get_node(node_id).get_state();
					const auto& entry_action = graph.get_node(lowest_node).get_parent_action(node_id);
					add_policy_entry(policy, entry_state, entry_action, lowest_node);
				}
			}
		}
		return policy;
	}

	void Planner::add_policy_entry(Policy& policy, const State& state, const Action& action, const Node_Id& node_id) const 
	{
		State perspective_shifted = state;
		perspective_shifted.shift_perspective(action.get_owner());

		for (State& shifted_state : perspective_shifted.split_into_globals()) {
			shifted_state.shift_perspective(action.get_owner());
			shifted_state.contract();
			policy.add_entry(shifted_state, action, node_id);
		}
	}

	std::unordered_map<size_t, size_t> Planner::calculate_best_value(Graph& graph) const 
	{
		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(graph.get_nodes().size());
		std::priority_queue < Node_Entry, std::vector<Node_Entry>, Node_Entry_Comparator> frontier(Node_Entry_Comparator(), frontier_reserve);
		std::unordered_map<size_t, size_t> best_value;
		std::unordered_map<size_t, size_t> children_visited;

		// TODO - Could add these by top down traversal to avoid adding unreachable leafs
		// This would also allow to only add an or-node to frontier when all its children have been visited
		for (const Node& node : graph.get_nodes()) 
		{
			if (node.get_children().empty()) 
			{
				frontier.push({ node.get_id(), 0 });
				best_value.insert({ node.get_id().id, 0 });
			}
		}

		while (!frontier.empty()) 
		{
			auto& [node_id, node_cost] = frontier.top();
			const Node& node = graph.get_node(node_id);
			frontier.pop();

			for (auto& [parent_id, action] : node.get_parents()) 
			{
				if (!graph.get_node(parent_id).is_solved())
				{
					continue;
				}

				++children_visited[parent_id.id];
				const Node& parent = graph.get_node(parent_id);
				
				if (parent.get_type() == Node_Type::Or) 
				{
					size_t new_node_cost = node_cost + action.get_cost();
					if (best_value.find(parent_id.id) == best_value.end()) 
					{
						best_value.insert({ parent_id.id, new_node_cost });
						frontier.push({ parent_id, new_node_cost });
					} 
					else if (new_node_cost < best_value.at(parent_id.id)) 
					{
						best_value[parent_id.id] = new_node_cost;
						frontier.push({ parent_id, new_node_cost });
						std::cerr << "Found node with better value in incorrect order " << node_id.id << " " << new_node_cost << std::endl;
					}
				} 
				else 
				{
					if (best_value.find(parent_id.id) == best_value.end()) 
					{
						best_value.insert({ parent_id.id, node_cost });
					} 
					else if (node_cost > best_value.at(parent_id.id)) 
					{
						best_value[parent_id.id] = node_cost;
					}

					if (children_visited.at(parent_id.id) == parent.get_children().size()) 
					{
						frontier.push({ parent_id, best_value[parent_id.id] });
					}
				}
			}
		}
		return best_value;
	}
	

	void Planner::propogate_dead_end_node(Graph& graph, Node& node) const
	{
		node.set_dead();
		if (node.is_root_node()) 
		{
			return;
		}

		std::deque<Node_Id> frontier;
		std::unordered_set<size_t> visited;
		auto& parents = node.get_parents();
		
		for (const auto& [parent_node, parent_action]: parents) 
		{
			frontier.push_back(parent_node);
			visited.insert(parent_node.id);
		}

		Node_Id current_node_id;
		while (!frontier.empty()) 
		{
			current_node_id = frontier.front();
			frontier.pop_front();

			Node& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_dead(graph)) 
			{
				if (current_node.is_root_node()) 
				{
					return;
				}
				
				auto& parents = current_node.get_parents();
				for (auto& parent : parents) 
				{
					if (visited.find(parent.first.id) == visited.end()) 
					{
						frontier.push_back(parent.first);
						visited.insert(parent.first.id);
					}
				}
			}
		}
	}



	void Planner::propogate_solved_node(Graph& graph, Node& node) const
	{
		node.set_solved();
		
		if (node.is_root_node()) 
		{
			return;
		}

		std::deque<Node_Id> frontier;
		std::unordered_set<size_t> visited;
		for (auto& [parent_node, parent_action] : node.get_parents())
		{
			frontier.push_back(parent_node);
			visited.insert(parent_node.id);
		}


		Node_Id current_node_id;
		while (!frontier.empty()) 
		{
			current_node_id = frontier.front();
			frontier.pop_front();
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_solved(graph)) 
			{
				if (current_node.is_root_node()) 
				{
					return;
				}
				
				auto& parents = current_node.get_parents();
				for (auto& parent : parents) 
				{
					if (visited.find(parent.first.id) == visited.end()) 
					{
						frontier.push_back(parent.first);
						visited.insert(parent.first.id);
					}
				}
			}
		}
	}
}
