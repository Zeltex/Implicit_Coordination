#include "Planner.hpp"

namespace del {

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(const Formula& goal_formula, Action_Library& action_library, const State& initial_state, const std::vector<Agent>& agents, const Domain& domain) const {

		std::unordered_map<size_t, Node_Id> visited_and;
		std::unordered_map<size_t, Node_Id> visited_or;

		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(100);
		std::vector<Node> nodes_reserve;
		nodes_reserve.reserve(100);
		Graph graph(std::move(frontier_reserve), std::move(nodes_reserve));
		graph.add_to_frontier(graph.create_root_node(initial_state));
		std::vector<size_t> debug_layer_size(10);
		size_t debug_counter = 0;
		while (!graph.is_frontier_empty()) {
			if (debug_counter > 1000) {
				break;
			}
			++debug_counter;

			Node_Id current_node = graph.get_next_from_frontier();
			action_library.load_actions(graph.get_node(current_node).get_state(), domain);

			while (action_library.has_action()) {
				const Action& action = action_library.get_next_action();
				State state_perspective_shift = perform_perspective_shift(graph.get_node(current_node).get_state(), action.get_owner());
				if (!is_action_applicable(state_perspective_shift, action)) {
					continue;
				}
				State state_product_update = perform_product_update(state_perspective_shift, action, agents);
				state_product_update = std::move(perform_k_bisimilar_contraction(state_product_update, BISIMILAR_DEPTH));

				bool bisim_exists = does_bisimilar_exist(graph, state_product_update, visited_and, current_node, Node_Id(), action);
				if (bisim_exists) continue;
				Node_Id action_node = graph.create_and_node(state_product_update, current_node, action);
				visited_and.insert({ graph.get_node(action_node).get_hash(), action_node });
				std::vector<State> global_states = split_into_global_states(state_product_update, action.get_owner());

				for (State& global_state : global_states) {
					bool bisim_exists = does_bisimilar_exist(graph, global_state, visited_or, action_node, current_node, Action());
					if (bisim_exists) continue;


					debug_layer_size[global_state.get_cost() / 100] ++;
					Node_Id global_agent_node = graph.create_or_node(global_state, action_node);
					if (is_goal_node(graph.get_node(global_agent_node), goal_formula)) {
						graph.get_node(global_agent_node).set_solved();
					} else {
						graph.add_to_frontier(global_agent_node);
					}
					visited_or.insert({ graph.get_node(global_agent_node).get_hash(), global_agent_node });
				}
				if (graph.get_node(action_node).check_if_solved(graph)) {
					propogate_solved_node(graph, action_node);
				}

			}
			if (graph.get_node(current_node).check_if_dead(graph)) {
				propogate_dead_end_node(graph, current_node);
			} else if (graph.get_node(current_node).check_if_solved(graph)) {
				propogate_solved_node(graph, current_node);
			}

			if (graph.get_root_node().is_dead()) {
				PRINT_GRAPH_DOT(graph, domain);
				PRINT_GRAPH(graph, domain);
				return Policy(false);
			}
			if (graph.get_root_node().is_solved()) {
				PRINT_GRAPH_DOT(graph, domain);
				PRINT_GRAPH(graph, domain);
				return extract_policy(graph);
			}
		}
		PRINT_GRAPH(graph, domain);
		PRINT_GRAPH_DOT(graph, domain);
		return Policy(false);
	}

	bool Planner::does_bisimilar_exist(Graph& graph, const State& state, std::unordered_map<size_t, Node_Id>& visited, const Node_Id& current_node_id, const Node_Id& parent_node_id, const Action& action) const{
		auto temp_hash = state.to_hash();
		auto bisim_nodes = visited.find(temp_hash);
		if (bisim_nodes == visited.end()) {
			return false;
		} else {
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.get_type() == Node_Type::Or) {
				if (is_bisimilar_on_path(graph, current_node_id, state)) {
					return true;
				}
			} else {
				if (is_bisimilar_on_path(graph, parent_node_id, state)) {
					return true;
				}
			}


			auto& child_node = graph.get_node((*bisim_nodes).second);
			graph.get_node(current_node_id).add_child(child_node.get_id());
			if (child_node.get_type() == Node_Type::And) {
				child_node.add_parent(current_node_id, action);
			} else {
				child_node.add_parent(current_node_id);
			}
			return true;
		}
	}

	const Action& Planner::get_next_action(const std::vector<Action>& normal_actions, const std::vector<Action>& announce_actions, size_t counter) const {
		if (counter < normal_actions.size()) {
			return normal_actions.at(counter);
		} else {
			return announce_actions.at(counter - normal_actions.size());
		}
	}

	bool Planner::is_bisimilar_on_path(Graph& graph, Node_Id node_id, const State& state) const {
		auto& node = graph.get_node(node_id);
		auto state_hash = state.to_hash();
		if (node.is_root_node()) {
			return false;
		}

		std::deque<Node_Id> frontier = { node_id };
		// TODO - This should have better handling for false positives
		std::unordered_set<size_t> visited_or;
		std::unordered_set<size_t> visited_and;

		while (!frontier.empty()) {
			Node_Id current_node_id = frontier.front();
			frontier.pop_front();

			auto& current_node = graph.get_node(current_node_id);
			if (current_node.get_type() == Node_Type::And) {
				if (visited_and.find(current_node.get_hash()) != visited_and.end()) {
					continue;
				}
				visited_and.insert(current_node.get_hash());
			} else {
				if (visited_or.find(current_node.get_hash()) != visited_or.end()) {
					continue;
				}
				visited_or.insert(current_node.get_hash());
			}
			if (current_node.get_hash() == state_hash) {
				return true;
			} else {
				if (current_node.is_root_node()) {
					continue;
				}
				auto& parents = current_node.get_parents();
				for (auto& parent : parents) {
					frontier.push_back(parent.first);
				}
			}
		}
		return false;
	}

	Policy Planner::extract_policy(Graph& graph) const {
		Node_Id temp2 = { 0 };
		auto temp = extract_policy_inner(graph, graph.get_root_node().get_id(), temp2);
		if (temp.has_value()) {
			return Policy(true, std::move(temp.value()));
		}
		return Policy(false);
	}

	std::optional< std::vector<std::pair<State, Action>>> Planner::extract_policy_inner(Graph& graph, const Node_Id& current_node_id, const Node_Id& parent_node_id) const {
		std::vector<std::pair<State, Action>> result;
		Node& current_node = graph.get_node(current_node_id);

		if (!current_node.is_solved() || current_node.is_dead()) return {};

		if (current_node.get_type() == Node_Type::And) {
			for (auto& child : current_node.get_children()) {
				auto policy = extract_policy_inner(graph, child, current_node_id);
				if (!policy.has_value()) {
					return {};
				} else {
					result.insert(result.begin(), policy.value().begin(), policy.value().end());
				}
			}
			const auto& state = graph.get_node(parent_node_id).get_state();
			const auto& action = current_node.get_parent_action(parent_node_id);
			const auto perspective_shifted = perform_perspective_shift(state, action.get_owner());
			for (auto global : split_into_global_states(perspective_shifted, action.get_owner())) {
				result.emplace_back(global, action);
			}
			return result;
		} else {
			for (auto& child : current_node.get_children()) {
				auto policy = extract_policy_inner(graph, child, current_node_id);
				if (policy.has_value()) {
					// TODO - Only assign if new policy is better than current
					if (result.empty() || policy.value().size() < result.size()) {
						result = std::move(policy.value());
					}
				}
			}
			return result;
		}
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