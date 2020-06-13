#pragma once

#include <vector>

#include "Node.hpp"
#include "Action.hpp"
#include "State.hpp"
#include "DEL_Operations.hpp"
#include "Agent.hpp"
#include "Graph.hpp"
#include "Types.hpp"
#include "Formula.hpp"
#include "Action_Library.hpp"

namespace del {

	class Planner {
	public:
		bool find_policy(Formula formula, Action_Library action_library);
	private:
		void extract_policy();
		void propogate_dead_end_node(Node& node);
		bool is_goal_node(Node& node, Formula& goal_formula);
		bool is_root_node(Node& node);
		bool is_valid_state(State state);
		std::vector<Agent> get_all_agents();
	};
}