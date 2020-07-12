#pragma once

#include <vector>
#include <tuple>

#include "State.hpp"
#include "Action.hpp"
#include "Misc.hpp"
#include "DEL_Operations.hpp"

namespace del {
	class Policy {
	public:

		Policy(bool solved) : solved(solved) {}
		bool is_solved() const;
		void add_policy_entry(State state, Action action);
		std::tuple<Action, bool> get_action(State state);

		std::string to_graph(const Domain& domain) const;
		std::string to_string(const Domain& domain) const;
	private:
		bool solved;
		std::vector<std::pair<State, Action>> policy;
	};
}