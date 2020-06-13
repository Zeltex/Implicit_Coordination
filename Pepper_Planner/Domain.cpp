#include "Domain.hpp"

namespace del {
	bool Domain::find_policy(Formula goal_formula) {
		Graph graph;
		while (true) {
			if (graph.is_frontier_empty()) {
				return false;
			}

			Node_Id current_node = graph.get_next_from_frontier();
			if (is_goal_node(graph.get_node(current_node), goal_formula)) {
				if (is_root_node(graph.get_node(current_node))) {
					extract_policy();
					return true;
				}
				else {
					continue;
				}
			}

			bool found_applicable_action = false;
			for (Action action : get_all_actions()) {
				State temp = perform_product_update(graph.get_node(current_node).get_state(), action);
				if (!is_valid_state(temp)) {
					continue;
				}
				else {
					found_applicable_action = true;
				}
				Node_Id action_node = graph.create_node(temp, current_node);

				for (Agent agent : get_all_agents()) {
					State perspective_shifted = perform_perspective_shift(graph.get_node(action_node).get_state(), agent);
					std::vector<State> global_states = split_into_global_states(perspective_shifted);

					for (State state : global_states) {
						Node_Id global_agent_node = graph.create_node(state, action_node);
						graph.add_to_frontier(global_agent_node);
					}
				}
			}
			if (!found_applicable_action) {
				propogate_dead_end_node(graph.get_node(current_node));
			}
		}
		return false;
	}


	void Domain::extract_policy() {
		throw;
	}

	void Domain::propogate_dead_end_node(Node& node) {
		throw;
	}

	bool Domain::is_goal_node(Node& node, Formula& goal_formula) {
		return node.valuate(goal_formula);
	}

	bool Domain::is_valid_state(State state) {
		throw;
	}

	bool Domain::is_root_node(Node& node) {
		return node.is_root_node();
	}

	std::vector<Action> Domain::get_all_actions() {
		throw;
	}

	std::vector<Agent> Domain::get_all_agents() {
		throw;
	}


}