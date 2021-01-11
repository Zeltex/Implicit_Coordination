#pragma once
#include "Formula_Input_Interface.hpp"

namespace del {
	class State;
	class Domain;
	class Formula_Input_Impl : public Formula_Input_Interface {
	public:
		Formula_Input_Impl(const State* state, const Domain* domain) : state(state), domain(domain) {}
		Formula_Input_Impl(const State* state) : state(state), domain(nullptr) {}
		bool valuate_prop(Proposition_Instance prop, const size_t world_id) const;
		std::vector<size_t> get_reachable_worlds(size_t agent_id, size_t world_id) const;

	private:
		const State* state;
		const Domain* domain;
	};
}

