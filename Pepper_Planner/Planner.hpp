#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "Node.hpp"
#include "Action.hpp"
#include "State.hpp"
#include "Agents.hpp"
#include "Graph.hpp"
#include "Types.hpp"
#include "Formula.hpp"
#include "Action_Library.hpp"
#include "Policy.hpp"


namespace del {

	class Planner {
	public:
		Policy find_policy(const Formula& formula, Action_Library& action_library, const Domain& domain, Agent planning_agent, const bool is_benchmark=false) const;
	private:
		Policy extract_policy(Graph& graph) const;
		void add_policy_entry(Policy& policy, const State& state, const Action& action, const Node_Id& node_id) const;
		std::unordered_map<size_t, size_t> calculate_best_value(Graph& graph) const;
		Policy calculate_policy(Graph& graph, const std::unordered_map<size_t, size_t>& best_value) const;
		std::optional<Policy> check_root(Graph& graph, const Domain& domain, const bool is_benchmark) const;
		void check_node(Graph& graph, Node& node, bool check_dead) const;
		void check_node(Graph& graph, Node_Id node, bool check_dead=true) const;
		void propogate_dead_end_node(Graph& graph, Node& node) const;
		void propogate_solved_node(Graph& graph, Node& node) const;
	};
}