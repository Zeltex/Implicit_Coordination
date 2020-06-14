#include "Planner.hpp"

namespace del {
	bool Planner::find_policy(Formula goal_formula, Action_Library action_library) const {
		Graph graph;
		while (true) {
			if (graph.is_frontier_empty()) {
				return false;
			}

			Node_Id current_node = graph.get_next_from_frontier();
			if (is_goal_node(graph.get_node(current_node), goal_formula)) {
				propogate_solved_node(graph, current_node);
				if (graph.get_root_node().is_solved()) {
					extract_policy(graph);
					return true;
				}
				else {
					continue;
				}
			}

			bool found_applicable_action = false;
			for (Action action : action_library.get_actions()) {
				State temp = perform_product_update(graph.get_node(current_node).get_state(), action);
				if (!is_valid_state(temp)) {
					continue;
				}
				else {
					found_applicable_action = true;
				}
				Node_Id action_node = graph.create_and_node(temp, current_node, action);

				for (Agent agent : get_all_agents()) {
					State perspective_shifted = perform_perspective_shift(graph.get_node(action_node).get_state(), agent);
					std::vector<State> global_states = split_into_global_states(perspective_shifted, agent.get_id());

					for (State state : global_states) {
						Node_Id global_agent_node = graph.create_or_node(state, action_node);
						graph.add_to_frontier(global_agent_node);
					}
				}
			}
			if (!found_applicable_action) {
				propogate_dead_end_node(graph, current_node);
				if (graph.get_root_node().is_dead()) {
					return false;
				}
			}
		}
		return false;
	}


	void Planner::extract_policy(Graph& graph) const {


		throw;
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

	std::vector<Agent> Planner::get_all_agents() const {
		throw;
	}


}