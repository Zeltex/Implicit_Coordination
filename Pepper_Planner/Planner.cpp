#include "Planner.hpp"
#include "Node_Comparator.hpp"

namespace del {

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(const Formula& goal_formula, Action_Library& action_library, const State& initial_state, const std::vector<Agent>& agents, const Domain& domain) const {
		constexpr size_t initial_node_size = 10000;
		Graph graph(initial_node_size, initial_state);
		Node_Comparator history(graph.get_root_node());
		std::vector<size_t> debug_layer_size(10);
		while (!graph.is_frontier_empty()) {
			Node_Id current_node = graph.get_next_from_frontier();
			action_library.load_actions(graph.get_node(current_node).get_state(), domain);

			while (action_library.has_action()) {
				const Action& action = action_library.get_next_action();
				State state_perspective_shift = perform_perspective_shift(graph.get_node(current_node).get_state(), action.get_owner());
				if (!is_action_applicable(state_perspective_shift, action)) {
					continue;
				}
				State temp_state = perform_product_update(state_perspective_shift, action, agents);
				State state_product_update = std::move(perform_k_bisimilar_contraction(std::move(temp_state), BISIMILAR_DEPTH));

				auto [bisim_exists, child_node_id] = history.does_bisimilar_exist_and(graph, state_product_update, current_node);
				if (child_node_id.has_value()) graph.set_parent_child(current_node, child_node_id.value(), action);
				if (bisim_exists) continue;
				
				Node_Id action_node = graph.create_and_node(state_product_update, current_node, action);
				history.insert(graph.get_node(action_node));
				std::vector<State> global_states = split_into_global_states(state_product_update, action.get_owner());

				for (State& global_state : global_states) {

					auto [bisim_exists, child_node_id] = history.does_bisimilar_exist_or(graph, global_state, action_node);
					if (child_node_id.has_value()) graph.set_parent_child(action_node, child_node_id.value(), action);
					if (bisim_exists) {
						if (!child_node_id.has_value()) {
							graph.get_node(action_node).set_dead();
							break;
						}
						continue;
					}

					debug_layer_size[global_state.get_cost() / 100] ++;
					Node_Id global_agent_node = graph.create_or_node(global_state, action_node);
					if (is_goal_node(graph.get_node(global_agent_node), goal_formula)) {
						graph.get_node(global_agent_node).set_solved();
					} else {
						graph.add_to_frontier(global_agent_node);
					}
					history.insert(graph.get_node(global_agent_node));
				}
				check_node(graph, action_node, false);
			}
			check_node(graph, current_node);
			auto policy = check_root(graph, domain);
			if (policy.has_value()) return policy.value();
		}
		PRINT_GRAPH(graph, domain);
		PRINT_GRAPH_DOT(graph, domain);
		return Policy(false);
	}

	std::optional<Policy> Planner::check_root(Graph& graph, const Domain& domain) const {
		if (graph.get_root_node().is_dead()) {
			PRINT_GRAPH_DOT(graph, domain);
			PRINT_GRAPH(graph, domain);
			std::cout << "No policy found\n";
			return Policy(false);
		}
		if (graph.get_root_node().is_solved()) {
			PRINT_GRAPH_DOT(graph, domain);
			PRINT_GRAPH(graph, domain);
			std::cout << "Policy found\n";
			return extract_policy(graph);
		}
		return {};
	}

	void Planner::check_node(Graph& graph, Node_Id node, bool check_dead) const {
		if (check_dead && graph.get_node(node).check_if_dead(graph)) {
			propogate_dead_end_node(graph, node);
		} else if (graph.get_node(node).check_if_solved(graph)) {
			propogate_solved_node(graph, node);
		}
	}

	const Action& Planner::get_next_action(const std::vector<Action>& normal_actions, const std::vector<Action>& announce_actions, size_t counter) const {
		if (counter < normal_actions.size()) {
			return normal_actions.at(counter);
		} else {
			return announce_actions.at(counter - normal_actions.size());
		}
	}

	Policy Planner::extract_policy(Graph& graph) const {
		auto best_value = calculate_best_value(graph);
		return calculate_policy(graph, best_value);
	}

	Policy Planner::calculate_policy(Graph& graph, const std::unordered_map<size_t, size_t>& best_value) const{
		std::deque<Node_Id> frontier = { graph.get_root_node().get_id() };
		std::unordered_set<size_t> visited_or = { graph.get_root_node().get_id().id };
		std::unordered_set<size_t> visited_and;

		Policy policy(true);

		while (!frontier.empty()) {
			auto node_id = frontier.front();
			frontier.pop_front();
			auto& node = graph.get_node(node_id);

			if (node.get_type() == Node_Type::And) {
				for (auto& child : node.get_children()) {
					if (!graph.get_node(child).is_solved()) continue;
					if (visited_or.find(child.id) != visited_or.end()) continue;
					visited_or.insert(child.id);

					frontier.push_back(child);
				}
			} else {
				size_t lowest_value = (size_t)-1;
				Node_Id lowest_node = { 0 };
				bool found_node = false;
				for (auto& child : node.get_children()) {
					if (!graph.get_node(child).is_solved()) continue;

					if (best_value.at(child.id) < lowest_value) {
						lowest_value = best_value.at(child.id);
						lowest_node = child;
						found_node = true;
					}
				}
				if (found_node) {
					const auto& entry_state = graph.get_node(node_id).get_state();
					const auto& entry_action = graph.get_node(lowest_node).get_parent_action(node_id);
					add_policy_entry(policy, entry_state, entry_action);

					if (visited_and.find(lowest_node.id) != visited_and.end()) continue;
					visited_and.insert(lowest_node.id);
					frontier.push_back(lowest_node);
				}
			}
		}
		return policy;
	}

	void Planner::add_policy_entry(Policy& policy, const State& state, const Action& action) const {
		const auto perspective_shifted = perform_perspective_shift(state, action.get_owner());
		for (auto global : split_into_global_states(perspective_shifted, action.get_owner())) {
			policy.add_entry(global, action);
		}
	}

	std::unordered_map<size_t, size_t> Planner::calculate_best_value(Graph& graph) const {
		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(graph.get_nodes().size());
		std::priority_queue < Node_Entry, std::vector<Node_Entry>, Node_Entry_Comparator> frontier(Node_Entry_Comparator(), frontier_reserve);
		std::unordered_map<size_t, size_t> best_value;
		std::unordered_map<size_t, size_t> children_visited;

		// TODO - Could add these by top down traversal to avoid adding unreachable leafs
		for (auto& node : graph.get_nodes()) {
			if (node.get_children().empty()) {
				frontier.push({ node.get_id(), node.get_cost() });
				best_value.insert({ node.get_id().id, node.get_cost() });
			}
		}

		while (!frontier.empty()) {
			auto node_entry = frontier.top();
			auto& node = graph.get_node(node_entry.id);
			frontier.pop();

			for (auto& [parent_id, action] : node.get_parents()) {
				if (!graph.get_node(parent_id).is_solved()) continue;

				++children_visited[parent_id.id];
				auto& parent = graph.get_node(parent_id);
				if (parent.get_type() == Node_Type::Or) {
					if (best_value.find(parent_id.id) == best_value.end()) {
						best_value.insert({ parent_id.id, node_entry.cost });
						frontier.push({ parent_id, node_entry.cost });
					} else if (node_entry.cost < best_value.at(parent_id.id)) {
						best_value[parent_id.id] = node_entry.cost;
						frontier.push({ parent_id, node_entry.cost });
						std::cout << "Found node with better value in incorrect order " << node_entry.id.id << " " << node_entry.cost << std::endl;
					}
				} else {
					if (best_value.find(parent_id.id) == best_value.end()) {
						best_value.insert({ parent_id.id, node_entry.cost });
					} else if (node_entry.cost > best_value.at(parent_id.id)) {
						best_value[parent_id.id] = node_entry.cost;
					}
					if (children_visited.at(parent_id.id) == parent.get_children().size()) {
						frontier.push({ parent_id, best_value[parent_id.id] });
					}
				}
			}
		}
		return best_value;
	}
	

	void Planner::propogate_dead_end_node(Graph& graph, Node_Id node_id) const {
		auto& node = graph.get_node(node_id);
		node.set_dead();
		if (node.is_root_node()) {
			return;
		}

		std::deque<Node_Id> frontier;
		auto& parents = node.get_parents();
		for (auto& parent : parents) {
			frontier.push_back(parent.first);
		}

		Node_Id current_node_id;
		while (!frontier.empty()) {
			current_node_id = frontier.front();
			frontier.pop_front();

			auto& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_dead(graph)) {
				if (current_node.is_root_node()) {
					return;
				}
				auto& parents = current_node.get_parents();
				for (auto& parent : parents) {
					frontier.push_back(parent.first);
				}
			}
		}
	}



	void Planner::propogate_solved_node(Graph& graph, Node_Id node_id) const {
		auto& node = graph.get_node(node_id);
		node.set_solved();
		if (node.is_root_node()) {
			return;
		}

		std::deque<Node_Id> frontier;
		auto& parents = node.get_parents();
		for (auto& parent : parents) {
			frontier.push_back(parent.first);
		}

		Node_Id current_node_id;
		while (!frontier.empty()) {
			current_node_id = frontier.front();
			frontier.pop_front();
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_solved(graph)) {
				if (current_node.is_root_node()) {
					return;
				}
				auto& parents = current_node.get_parents();
				for (auto& parent : parents) {
					frontier.push_back(parent.first);
				}
			}
		}
	}

	bool Planner::is_goal_node(const Node& node, const Formula& goal_formula) const {
		return node.valuate(goal_formula);
	}

	bool Planner::is_valid_state(const State& state) const {
		return state.get_worlds_count() > 0 && state.get_designated_worlds_count() > 0;
	}

	bool Planner::is_root_node(const Node& node) const {
		return node.is_root_node();
	}

	const std::vector<Agent>& Planner::get_all_agents(const Domain& domain) const {
		return domain.get_agents();
	}
}