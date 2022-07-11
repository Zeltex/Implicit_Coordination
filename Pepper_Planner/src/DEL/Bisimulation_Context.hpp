#pragma once

#include "State.hpp"

namespace del::bisimulation_context {
	//State contract(const State& state);
	State contract(const State& state, const std::set<World_Id>& designated_worlds);
}