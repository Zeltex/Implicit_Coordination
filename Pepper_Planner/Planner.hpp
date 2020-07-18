#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "Action.hpp"
#include "State.hpp"
#include "DEL_Operations.hpp"
#include "Agent.hpp"
#include "Graph.hpp"
#include "Types.hpp"
#include "Formula.hpp"
#include "Action_Library.hpp"
#include "Policy.hpp"


namespace del {

	class Planner {
	public:
		Policy find_policy(const Formula& formula, Action_Library& action_library, const State& initial_state, const std::vector<Agent>& agents, const Domain& domain) const;
	private:
		std::pair<bool, bool> does_bisimilar_exist(Graph& graph, const State& state, std::unordered_map<size_t, Node_Id>& visited, const Node_Id& current_node, const Node_Id& parent_node_id, const Action& action) const;
		Policy extract_policy(Graph& graph) const;
		std::optional< std::vector<std::pair<State, Action>>>  extract_policy_inner(Graph& graph, const Node_Id& current_node_id, const Node_Id& parent_node_id) const;
		void propogate_dead_end_node(Graph& graph, Node_Id node) const;
		void propogate_solved_node(Graph& graph, Node_Id node_id) const;
		bool is_goal_node(const Node& node, const Formula& goal_formula) const;
		bool is_root_node(const Node& node) const;
		bool is_valid_state(const State& state) const;
		bool is_bisimilar_on_path(Graph& graph, Node_Id node, const State& state) const;
		const std::vector<Agent>& get_all_agents(const Domain& domain) const;
		const Action& get_next_action(const std::vector<Action>& normal_actions, const std::vector<Action>& announce_actions, size_t counter) const;

	};
}