#pragma once

#include <vector>
#include <unordered_map>

#include "State.hpp"
#include "Action.hpp"
#include "Agent.hpp"


namespace del {
	bool is_action_applicable(const State& state, const Action& action);
	State perform_product_update(const State& state, const Action& action);
	State perform_perspective_shift(const State& state, const Agent& agent);
	std::vector<State> split_into_global_states(const State& state, const Agent_Id agent);
	bool are_states_bisimilar(const State& state1, const State& state2);
}