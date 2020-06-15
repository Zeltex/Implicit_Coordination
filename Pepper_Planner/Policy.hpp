#pragma once

#include <vector>
#include "State.hpp"
#include "Action.hpp"
#include "Misc.hpp"

namespace del {
	class Policy {
	public:

		Policy(bool solved) : solved(solved) {}
		bool is_solved() const;
		void add_policy_entry(State state, Action action);

		std::string to_string() const;
	private:
		bool solved;
		std::vector<std::pair<State, Action>> policy;
	};
}