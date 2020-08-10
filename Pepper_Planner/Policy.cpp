#include "Policy.hpp"
#include "Node_Comparator.hpp"
#include "Core.hpp"

namespace del {

	bool Policy::is_solved() const {
		return solved;
	}

	std::optional<Action> Policy::get_action(const State& state, Agent_Id preferred_agent) const {
		std::vector<size_t> agent_hashes;
		std::vector<State> agent_states;
		for (size_t agent = 0; agent < state.get_number_of_agents(); ++agent) {
			State temp = state;
			temp = std::move(perform_perspective_shift(temp, { agent }));
			temp.remove_unreachable_worlds();
			temp = std::move(perform_k_bisimilar_contraction(temp, BISIMILAR_DEPTH));
			agent_hashes.emplace_back(temp.to_hash());
			agent_states.push_back(std::move(temp));
		}

		int agent_counter = 0;
		for (auto& hash : agent_hashes) {
			while (true) {
				auto potential_match = policy.find(hash);
				if (potential_match == policy.end()) {
					break;
				}

				auto& [policy_state, policy_actions] = (*potential_match).second;
				if (are_states_bisimilar(policy_state, agent_states[agent_counter])) {
					for (auto& [policy_action, policy_node] : policy_actions) {
						if (policy_action.get_owner().id == agent_counter) {
							return policy_action;
						}
					}
				}
				++hash;
			}
			++agent_counter;
		}
		return {};
	}

	void Policy::add_entry(const State& state, const Action& action, const Node_Id& node_id) {
		auto hash = state.to_hash();
		while (true) {
			auto potential_match = policy.find(hash);
			if (potential_match == policy.end()) {
				policy.insert({ hash, Policy_Entry{state, {{action, node_id}}} });
				return;
			}

			// TODO - Need to not add duplicates
			auto& [policy_state, policy_actions] = (*potential_match).second;
			if (are_states_bisimilar(policy_state, state)) {
				policy_actions.emplace_back(action, node_id);
				return;
			}
			++hash;
		}

	}

	std::string Policy::to_graph(const Domain& domain) const {
		std::string result;
		size_t counter = 0;
		//for (auto& entry : policy) {
		//	std::string counter_s = std::to_string(counter);
		//	result += "subgraph cluster_"
		//		+ counter_s
		//		+ "{label=\"entry"
		//		+ counter_s
		//		+ "\";\nsubgraph cluster_s"
		//		+ counter_s
		//		+ "{"
		//		//+ entry.first.to_graph("s" + counter_s, domain)
		//		+ std::to_string(entry.first)
		//		+ "} subgraph cluster_a"
		//		+ counter_s
		//		+ "{label=\""
		//		+ entry.second.get_name()
		//		+ "\"\n"
		//		+ entry.second.to_graph("a" + counter_s, domain)
		//		+ "}"
		//		+ "s" 
		//		+ counter_s
		//		+ "0->a"
		//		+ counter_s
		//		+ "0[ltail=cluster_s"
		//		+ counter_s
		//		+ ", lhead=cluster_a"
		//		+ counter_s
		//		+ "];}\n";
		//	counter++;
		//}
		return result;
	}

	std::string Policy::to_string(const Domain& domain) const {
		size_t indentation = 4;
		std::string result = get_indentation(indentation) + " Policy";
		size_t counter = 0;
		//for (auto policy_entry : policy) {
		//	result += "\n" 
		//		+ get_indentation(indentation - 1) 
		//		+ " Entry " 
		//		+ std::to_string(counter) 
		//		+ "\n" 
		//		//+ policy_entry.first.to_string(indentation - 2, domain) 
		//		+ std::to_string(policy_entry.first)
		//		+ "\n" 
		//		+ policy_entry.second.to_string(indentation - 2, domain) 
		//		+ "\n";
		//	counter++;
		//}
		return result;
	}
}