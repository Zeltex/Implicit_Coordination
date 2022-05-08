#pragma once
#include "Formula_Input_Interface.hpp"

namespace del {
	class State;
	class Domain;
	class Formula_Input_Impl : public Formula_Input_Interface {
	public:
		Formula_Input_Impl(const State* state, const Domain* domain) : state(state), domain(domain) {}
		Formula_Input_Impl(const State* state) : state(state), domain(nullptr) {}
		virtual bool valuate_prop(const Proposition& prop, const size_t world_id) const override;
		virtual std::set<size_t> get_reachable_worlds(const Proposition& agent_id, size_t world_id) const override;

	private:
		const State* state;
		const Domain* domain;
	};
}

