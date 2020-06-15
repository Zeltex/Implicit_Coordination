#include "Policy.hpp"

namespace del {

	bool Policy::is_solved() const {
		return solved;
	}

	void Policy::add_policy_entry(State state, Action action) {
		policy.emplace_back(state, action);
	}

	std::tuple<Action, bool> Policy::get_action(State state) {
		for (auto& policy_entry : policy) {
			if (are_states_bisimilar(policy_entry.first, state)) {
				return { policy_entry.second, true };
			}
		}
		return { Action({ 0 }, 0), false };
	}

	std::string Policy::to_string() const {
		size_t indentation = 4;
		std::string result = get_indentation(indentation) + " Policy";
		size_t counter = 0;
		for (auto policy_entry : policy) {
			result += "\n" 
				+ get_indentation(indentation - 1) 
				+ " Entry " 
				+ std::to_string(counter) 
				+ "\n" 
				+ policy_entry.first.to_string(indentation - 2) 
				+ "\n" 
				+ policy_entry.second.to_string(indentation - 2) 
				+ "\n";
			counter++;
		}
		return result;
	}
}