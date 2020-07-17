#include "Planner.hpp"

namespace del {

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(const Formula& goal_formula, const Action_Library& action_library, const State& initial_state, const std::vector<Agent>& agents, const Domain& domain) const {

		std::unordered_map<size_t, Node_Id> visited_and;
		std::unordered_map<size_t, Node_Id> visited_or;

		std::vector<Node_Entry> frontier_reserve;
		frontier_reserve.reserve(100);
		std::vector<Node> nodes_reserve;
		nodes_reserve.reserve(100);
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
				State temp_product_update = perform_product_update(temp_perspective_shift, action, agents);

				Node_Id dummy_node;
				auto [bisim_exists, action_applicable] = does_bisimilar_exist(graph, temp_product_update, visited_and, current_node, dummy_node, action);
				found_applicable_action |= action_applicable;
				Node_Id action_node;
				if (bisim_exists) continue;
				//if (graph.get_root_node().is_dead()) {
				//	PRINT_GRAPH_DOT(graph, domain);
				//	PRINT_GRAPH(graph, domain);
				//	return Policy(false);
				//}
				//if (graph.get_root_node().is_solved()) {
				//	PRINT_GRAPH_DOT(graph, domain);
				//	PRINT_GRAPH(graph, domain);
				//	return extract_policy(graph);
				//}
				action_node = graph.create_and_node(temp_product_update, current_node, action);
				visited_and.insert({ graph.get_node(action_node).get_hash(), action_node });
				
				found_applicable_action = true;
				


				std::vector<State> global_states = split_into_global_states(temp_product_update, action.get_owner());

				for (State state : global_states) {
					Action dummy;
					auto [bisim_exists, action_applicable] = does_bisimilar_exist(graph, state, visited_or, action_node, current_node, dummy);
					if (bisim_exists) continue;


					layer_size[state.get_cost() / 100] ++;
					Node_Id global_agent_node = graph.create_or_node(state, action_node);
					graph.add_to_frontier(global_agent_node);
					visited_or.insert({ graph.get_node(global_agent_node).get_hash(), global_agent_node });
				}
				if (graph.get_node(action_node).check_if_solved(graph)) {
					propogate_solved_node(graph, action_node);
					if (graph.get_root_node().is_solved()) {
						PRINT_GRAPH_DOT(graph, domain);
						PRINT_GRAPH(graph, domain);
						return extract_policy(graph);
					}
				}

			}
			if (!found_applicable_action) {
				propogate_dead_end_node(graph, current_node);
				if (graph.get_root_node().is_dead()) {
					PRINT_GRAPH_DOT(graph, domain);
					PRINT_GRAPH(graph, domain);
					return Policy(false);
				}
			} else if (graph.get_node(current_node).check_if_solved(graph)) {
				propogate_solved_node(graph, current_node);
				if (graph.get_root_node().is_solved()) {
					PRINT_GRAPH_DOT(graph, domain);
					PRINT_GRAPH(graph, domain);
					return extract_policy(graph);
				}
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
		PRINT_GRAPH_DOT(graph, domain);
		return Policy(false);
	}

	std::pair<bool, bool> Planner::does_bisimilar_exist(Graph& graph, const State& state, std::unordered_map<size_t, Node_Id>& visited, const Node_Id& current_node_id, const Node_Id& parent_node_id, const Action& action) const{
		auto temp_hash = state.to_hash();
		auto bisim_nodes = visited.find(temp_hash);
		if (bisim_nodes == visited.end()) {
			return { false, true };
		} else {
			if (!are_states_bisimilar(state, graph.get_node((*bisim_nodes).second).get_state())) {
				size_t debug = 1;
			}
			auto& current_node = graph.get_node(current_node_id);
			if (current_node.get_type() == Node_Type::Or) {
				if (is_bisimilar_on_path(graph, current_node_id, state)) {
					return { true, false };
				}
			} else {
				if (is_bisimilar_on_path(graph, parent_node_id, state)) {
					return { true, false };
				}
			}


			auto& child_node = graph.get_node((*bisim_nodes).second);
			graph.get_node(current_node_id).add_child(child_node.get_id());
			if (child_node.get_type() == Node_Type::And) {
				child_node.add_parent(current_node_id, action);
			} else {
				child_node.add_parent(current_node_id);
			}
			//if (child_node.is_dead()) propogate_dead_end_node(graph, child_node.get_id());
			//if (child_node.is_solved()) propogate_solved_node(graph, child_node.get_id());
			return { true, true };
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

		while (!frontier.empty()) {
			Node_Id current_node_id = frontier.front();
			frontier.pop_front();

			auto& current_node = graph.get_node(current_node_id);
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

	//bool Planner::is_bisimilar_on_path(Graph& graph, Node_Id node_id) const {
	//	auto& node = graph.get_node(node_id);
	//	if (node.is_root_node()) {
	//		return false;
	//	}
	//	auto current_node_id = node.get_parent();
	//	while (true) {
	//		auto& current_node = graph.get_node(current_node_id);
	//		if (current_node.get_type() == Node_Type::Or && are_states_bisimilar(node.get_state(), current_node.get_state())) {
	//			return true;
	//		} else if (current_node.is_root_node()) {
	//			return false;
	//		} else {
	//			current_node_id = current_node.get_parent();
	//		}
	//	}
	//	return false;
	//}

	Policy Planner::extract_policy(Graph& graph) const {
		Policy policy(true);
		Node_Id temp2 = { 0 };
		auto temp = extract_policy_inner(graph, graph.get_root_node().get_id(), temp2);
		if (temp.has_value()) {
			for (auto& entry : temp.value()) {
				policy.add_policy_entry(entry.first, entry.second);
			}
		}

		//// {current_node, parent_node}
		//std::deque<std::pair<Node_Id, Node_Id>> frontier;
		//frontier.push_back({ graph.get_root_node().get_id(), {0} });
		//while (!frontier.empty()) {
		//	auto[current_node_id, parent_node_id] = frontier.back();
		//	frontier.pop_back();
		//	auto& current_node = graph.get_node(current_node_id);

		//	if (current_node.get_type() == Node_Type::And) {
		//		auto& parent = graph.get_node(parent_node_id);
		//		policy.add_policy_entry(parent.get_state(), current_node.get_parent_action(parent_node_id));
		//	}
		//	for (auto child_id : current_node.get_children()) {

		//		auto& child = graph.get_node(child_id);
		//		if (child.is_solved()) {
		//			frontier.push_back({ child_id, current_node_id });
		//			if (current_node.get_type() == Node_Type::Or) {
		//				break;
		//			}
		//		}
		//	}
		//}

		return policy;
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
			result.emplace_back(graph.get_node(parent_node_id).get_state(), current_node.get_parent_action(parent_node_id));
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
		while (true) {
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