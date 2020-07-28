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
		Policy extract_policy(Graph& graph) const;
		void add_policy_entry(Policy& policy, const State& state, const Action& action) const;
		std::unordered_map<size_t, size_t> calculate_best_value(Graph& graph) const;
		Policy calculate_policy(Graph& graph, const std::unordered_map<size_t, size_t>& best_value) const;
		std::optional<Policy> check_root(Graph& graph, const Domain& domain) const;
		void check_node(Graph& graph, Node_Id node) const;
		void propogate_dead_end_node(Graph& graph, Node_Id node) const;
		void propogate_solved_node(Graph& graph, Node_Id node_id) const;
		bool is_goal_node(const Node& node, const Formula& goal_formula) const;
		bool is_root_node(const Node& node) const;
		bool is_valid_state(const State& state) const;
		const std::vector<Agent>& get_all_agents(const Domain& domain) const;
		const Action& get_next_action(const std::vector<Action>& normal_actions, const std::vector<Action>& announce_actions, size_t counter) const;

	};
}