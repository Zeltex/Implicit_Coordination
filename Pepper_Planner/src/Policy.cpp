#include "Policy.hpp"

#include "Core.hpp"
#include "Node_Comparator.hpp"


#include <iostream>
#include <filesystem>
#include <fstream>

namespace del {

	bool Policy::is_solved() const {
		return solved;
	}

	const Action* Policy::get_action(const State& state, Agent_Id preferred_agent) const {
		std::vector<size_t> agent_hashes;
		std::vector<State> agent_states;
		for (size_t agent = 0; agent < state.get_number_of_agents(); ++agent) {
			State temp = state;
			temp.shift_perspective(Agent_Id{ agent });
			temp.remove_unreachable_worlds();
			temp = temp.contract();
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
				if (policy_state.is_bisimilar_to(agent_states[agent_counter])) {
					for (auto& [policy_action, policy_node] : policy_actions) {
						if (policy_action->get_owner().id == agent_counter) {
							return policy_action;
						}
					}
				}
				++hash;
			}
			++agent_counter;
		}
		return nullptr;
	}

	void Policy::add_entry(const State& state, const Action* action, const Node* node) {
		auto hash = state.to_hash();
		auto it = policy.find(hash);
		if (it == policy.end()) 
		{
			policy.insert({ hash, Policy_Entry{state, {{action, node}}} });
		}
	}

	std::string Policy::to_string(const Domain& domain) const {
		size_t indentation = 4;
		std::string result = get_indentation(indentation) + " Policy";
		size_t counter = 0;
		for (auto& [hash, entry] : policy) {
			auto temp_action_string = entry.actions.begin()->first->to_string(domain);
			result += "\n" 
				+ get_indentation(indentation - 1) 
				+ " Entry " 
				+ std::to_string(counter) 
				+ "\n" 
				+ std::to_string(hash)
				+ "\n" 
				+ entry.state.to_string(domain) 
				+ "\n"
				+ entry.actions.begin()->first->to_string(domain)
				+ "\n---------------------------------\n\n";
			std::cout << result << std::endl;
			counter++;
		}
		return result;
	}
}