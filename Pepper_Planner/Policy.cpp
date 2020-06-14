#include "Policy.hpp"

namespace del {

	bool Policy::is_solved() const {
		return solved;
	}

	void Policy::add_policy_entry(State state, Action action) {
		policy.emplace_back(state, action);
	}
}