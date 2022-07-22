#include "Policy.hpp"

#include "Agents.hpp"
#include "Core.hpp"
#include "Node_Comparator.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

namespace del {

	bool Policy::is_solved() const {
		return solved;
	}

	const Action* Policy::get_action(const State& state, const Agents* agents, Agent_Id preferred_agent) const {
		std::vector<size_t> agent_hashes;
		std::vector<State> agent_states;
		for (auto& agent : *agents)
		{ 
			State temp = state.shift_and_contract(&agent);
			PRINT(std::string("Looking for action for agent") + agent.get_name() + std::string(": ") + temp.to_string());
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

				auto& [policy_state, policy_actions] = potential_match->second;
				for (auto& [policy_action, policy_node] : policy_actions) {
					if (policy_action->get_owner()->get_id().id == agent_counter) {
						return policy_action;
					}
				}
			}
			++agent_counter;
		}
		return nullptr;
	}

	void Policy::add_entry(const State& state, const Action* action, const NodeBase* node)
	{
		State perspective_shifted = state.shift_and_contract(action->get_owner());

		std::vector<State> globals = perspective_shifted.split_into_globals();
		for (const State& global : globals)
		{
			auto shifted_state = global.shift_and_contract(action->get_owner());
			
			auto hash = shifted_state.to_hash();
			if (policy.find(hash) == policy.end())
			{
				policy.insert({ hash, Policy_Entry{shifted_state, {{action, node}}} });
			}
		}
	}

	bool Policy::try_visit(NodeBase* node)
	{
		if (visited.find(node) != visited.end())
		{
			return false;
		}

		visited.insert(node);
		return true;
	}

	std::string Policy::to_string() const {
		size_t indentation = 4;
		std::string indent_n(indentation, '-');
		std::string indent_n1(indentation - 1, '-');
		std::string result = indent_n + " Policy";
		size_t counter = 0;
		for (auto& [hash, entry] : policy) {
			auto temp_action_string = entry.actions.begin()->first->to_string();
			result += "\n" 
				+ indent_n1
				+ " Entry " 
				+ std::to_string(counter) 
				+ "\n" 
				+ std::to_string(hash)
				+ "\n" 
				+ entry.state.to_string() 
				+ "\n"
				+ entry.actions.begin()->first->to_string()
				+ "\n---------------------------------\n\n";
			std::cout << result << std::endl;
			counter++;
		}
		return result;
	}
}