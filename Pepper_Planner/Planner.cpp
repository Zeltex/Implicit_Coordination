#include "Planner.hpp"

namespace del {

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(const Formula& goal_formula, const Action_Library& action_library, const State& initial_state, const std::vector<Agent>& agents, const Domain& domain) const {

		std::unordered_map<size_t, State> visited;

		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(300000);
		std::vector<Node> nodes_reserve;
		nodes_reserve.reserve(300000);
		Graph graph(std::move(frontier_reserve), std::move(nodes_reserve));
		//Graph graph;
		Node_Id root_node = graph.create_root_node(initial_state);
		graph.add_to_frontier(root_node);
		size_t round_counter = 0;
		std::vector<size_t> layer_size(10);
		while (true) {
			//if (counter > 500) {
			//	graph.get_root_node().set_dead();
			//}
			round_counter++;

			if (graph.is_frontier_empty()) {
				PRINT_GRAPH_DOT(graph, domain);
				PRINT_GRAPH(graph, domain);
				return Policy(false);
			}

			Node_Id current_node = graph.get_next_from_frontier();
			if (is_goal_node(graph.get_node(current_node), goal_formula)) {
				propogate_solved_node(graph, current_node);
				if (graph.get_root_node().is_solved()) {
					PRINT_GRAPH_DOT(graph, domain);
					PRINT_GRAPH(graph, domain);
					return extract_policy(graph);
				} else {
					continue;
				}
			}

			if (is_bisimilar_on_path(graph, current_node)) {
				propogate_dead_end_node(graph, current_node);
				if (graph.get_root_node().is_dead()) {
					PRINT_GRAPH_DOT(graph, domain);
					PRINT_GRAPH(graph, domain);
					return Policy(false);
				}
			}

			auto& normal_actions = action_library.get_actions();
			auto announce_actions = action_library.get_announce_actions(graph.get_node(current_node).get_state(), domain);

			bool found_applicable_action = false;
			size_t counter = 0;
			while (counter < normal_actions.size() + announce_actions.size()) {
				const Action& action = get_next_action(normal_actions, announce_actions, counter);
				counter++;
				State temp_perspective_shift = perform_perspective_shift(graph.get_node(current_node).get_state(), action.get_owner());
				if (!is_action_applicable(temp_perspective_shift, action)) {
					continue;
				}
				found_applicable_action = true;

				State temp_product_update = perform_product_update(temp_perspective_shift, action, agents);


				auto temp_hash = temp_product_update.to_hash();
				if (visited.find(temp_hash) == visited.end()) {
					visited.insert({ temp_hash, temp_product_update });
				} else {
					continue;
				}

				Node_Id action_node = graph.create_and_node(temp_product_update, current_node, action);

				std::vector<State> global_states = split_into_global_states(temp_product_update, action.get_owner());

				for (State state : global_states) {
					layer_size[state.get_cost() / 100] ++;
					Node_Id global_agent_node = graph.create_or_node(state, action_node);
					graph.add_to_frontier(global_agent_node);


					//if (visited.find(temp_hash) != visited.end()) {
					//	size_t debug = 0;
					//} else {
					//	visited.insert({ temp_hash, state });
					//}

				}

			}
			if (!found_applicable_action) {
				propogate_dead_end_node(graph, current_node);
				if (graph.get_root_node().is_dead()) {
					PRINT_GRAPH_DOT(graph, domain);
					PRINT_GRAPH(graph, domain);
					return Policy(false);
				}
			}
		}
		PRINT_GRAPH_DOT(graph, domain);
		return Policy(false);
	}

	const Action& Planner::get_next_action(const std::vector<Action>& normal_actions, const std::vector<Action>& announce_actions, size_t counter) const {
		if (counter < normal_actions.size()) {
			return normal_actions.at(counter);
		} else {
			return announce_actions.at(counter - normal_actions.size());
		}
	}

	bool Planner::is_bisimilar_on_path(Graph& graph, Node_Id node_id) const {
		auto& node = graph.get_node(node_id);
		if (node.is_root_node()) {
			return false;
		}
		auto current_node_id = node.get_parent();
		while (true) {
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.get_type() == Node_Type::Or && are_states_bisimilar(node.get_state(), current_node.get_state())) {
				return true;
			} else if (current_node.is_root_node()) {
				return false;
			} else {
				current_node_id = current_node.get_parent();
			}
		}
		return false;
	}

	Policy Planner::extract_policy(Graph& graph) const {
		Policy policy(true);

		std::deque<Node_Id> frontier;
		frontier.push_back(graph.get_root_node().get_id());
		while (!frontier.empty()) {
			auto current_node_id = frontier.back();
			frontier.pop_back();
			auto& current_node = graph.get_node(current_node_id);

			if (current_node.get_type() == Node_Type::And) {
				auto& parent = graph.get_node(current_node.get_parent());
				policy.add_policy_entry(parent.get_state(), current_node.get_action());
			}
			for (auto child_id : current_node.get_children()) {

				auto& child = graph.get_node(child_id);
				if (child.is_solved()) {
					frontier.push_back(child_id);
					if (current_node.get_type() == Node_Type::Or) {
						break;
					}
				}
			}
		}

		return policy;
	}

	void Planner::propogate_dead_end_node(Graph& graph, Node_Id node_id) const {
		auto& node = graph.get_node(node_id);
		node.set_dead();
		if (node.is_root_node()) {
			return;
		}
		Node_Id current_node_id = node.get_parent();
		while (true) {
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_dead(graph)) {
				if (current_node.is_root_node()) {
					return;
				}
				current_node_id = current_node.get_parent();
			} else {
				break;
			}
		}
	}



	void Planner::propogate_solved_node(Graph& graph, Node_Id node_id) const {
		auto& node = graph.get_node(node_id);
		node.set_solved();
		if (node.is_root_node()) {
			return;
		}
		Node_Id current_node_id = node.get_parent();
		while (true) {
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.check_if_solved(graph)) {
				if (current_node.is_root_node()) {
					return;
				}
				current_node_id = current_node.get_parent();
			}
			else {
				break;
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