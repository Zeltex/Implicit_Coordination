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
		Policy find_policy(Domain& domain, const Agent* planning_agent, const bool is_benchmark=false) const;
	private:
		std::optional<Policy> check_root(Graph& graph, const bool is_benchmark) const;
	};
}