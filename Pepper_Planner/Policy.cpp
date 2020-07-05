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
	std::string Policy::to_graph(const std::vector<Agent>& agents, const Domain& domain) const {
		std::string result;
		size_t counter = 0;
		for (auto& entry : policy) {
			std::string counter_s = std::to_string(counter);
			result += "subgraph cluster_"
				+ counter_s
				+ "{label=\"entry"
				+ counter_s
				+ "\";\nsubgraph cluster_s"
				+ counter_s
				+ "{"
				+ entry.first.to_graph(agents, "s" + counter_s, domain)
				+ "} subgraph cluster_a"
				+ counter_s
				+ "{label=\""
				+ entry.second.get_name()
				+ "\"\n"
				+ entry.second.to_graph(agents, "a" + counter_s, domain)
				+ "}"
				+ "s" 
				+ counter_s
				+ "0->a"
				+ counter_s
				+ "0[ltail=cluster_s"
				+ counter_s
				+ ", lhead=cluster_a"
				+ counter_s
				+ "];}\n";
			counter++;
		}
		return result;
	}

	std::string Policy::to_string(const Domain& domain) const {
		size_t indentation = 4;
		std::string result = get_indentation(indentation) + " Policy";
		size_t counter = 0;
		for (auto policy_entry : policy) {
			result += "\n" 
				+ get_indentation(indentation - 1) 
				+ " Entry " 
				+ std::to_string(counter) 
				+ "\n" 
				+ policy_entry.first.to_string(indentation - 2, domain) 
				+ "\n" 
				+ policy_entry.second.to_string(indentation - 2, domain) 
				+ "\n";
			counter++;
		}
		return result;
	}
}