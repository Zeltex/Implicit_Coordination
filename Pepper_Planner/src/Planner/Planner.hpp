#pragma once

#include <vector>
#include <iostream>
#include <fstream>

#include "NodeBase.hpp"
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
		Policy find_policy(Domain& domain, Agent planning_agent, const bool is_benchmark=false) const;
	private:
		Policy extract_policy(Graph& graph) const;
		void add_policy_entry(Policy& policy, const State& state, const Action* action, const NodeBase* node) const;
		//std::unordered_map<const NodeBase*, size_t> calculate_best_value(Graph& graph) const;
		Policy calculate_policy(Graph& graph, const std::unordered_map<const NodeBase*, size_t>& best_value) const;
		std::optional<Policy> check_root(Graph& graph, const bool is_benchmark) const;
		void check_node(NodeBase* node, bool check_dead=true) const;
		//void propogate_dead_end_node(NodeBase* node) const;
		//void propogate_solved_node(NodeBase* node) const;
		void calculate_value(Graph& graph) const;
	};
}