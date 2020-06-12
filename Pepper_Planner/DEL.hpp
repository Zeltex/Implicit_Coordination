#pragma once

#include <vector>

#include "State.hpp"
#include "Action.hpp"
#include "Agent.hpp"


namespace del {
	State perform_product_update(State state, Action action);
	State perform_perspective_shift(State state, Agent agent);
	std::vector<State> split_into_global_states(State state);
}