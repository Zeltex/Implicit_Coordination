#include "General_Action.hpp"
#include "Action.hpp"
#include "Domain.hpp"

namespace del {
#define AGENT_STRING "agent"
#define REST_KEYWORD "_rest"
	void General_Action::set_owner(std::string type, std::string name) {
		owner = { type, name };
	}

	void General_Action::set_name(std::string name) {
		this->name = name;
	}

	void General_Action::set_designated_events(std::vector<std::string> designated_events) {
		this->designated_events = designated_events;
	}

	void General_Action::set_action_input(std::vector<std::pair<std::string, std::string>> inputs) {
		this->inputs = inputs;
	}

	void General_Action::create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list) {
		events.emplace_back(name, Event_Id{ events.size() }, std::move(preconditions), add_list, delete_list);
	}

	void General_Action::add_edge_condition(std::string agent, std::vector<Edge_Condition>&& edge_conditions_input) {
		edge_conditions.insert({ agent, std::move(edge_conditions_input) });
	} 

	void General_Action::set_amount_of_agents(size_t amount_of_agents) {
		//TODO - Might not be needed anymore
	}

	const std::vector<std::pair<std::string, std::string>>& General_Action::get_inputs() const {
		return inputs;
	}

	std::pair<std::string, std::string> General_Action::get_owner() const{
		return owner;
	}

	std::string General_Action::get_name() const {
		return name;
	}

	const std::vector<std::string>& General_Action::get_designated_events() const {
		return designated_events;
	}

	const std::vector<Action_Event>& General_Action::get_events() const {
		return events;
	}

	const std::unordered_map<std::string, std::vector<Edge_Condition>>& General_Action::get_edge_conditions() const {
		return edge_conditions;
	}

	Action General_Action::create_action(std::string owner, const std::vector<std::string>& arguments, const Domain& domain) const {

		if (!is_correct_type(this->owner.first, owner, domain)) {
			// TODO - Handle with custom exception
			std::cerr << "Tried to instantiate general_action with owner of wrong type\n";
			throw;
		}

		std::unordered_map<std::string, std::string> input_to_atom;
		input_to_atom.insert({ this->owner.second, owner });

		size_t counter = 0;
		for (auto& input : inputs) {
			
			if (!is_correct_type(input.first, arguments[counter], domain)) {
				// TODO - Handle with custom exception
				std::cerr << "Tried to instantiate general_action with argument of wrong type\n";
				throw;
			}

			if (input.second == this->owner.second) {
				if (owner != arguments[counter]) {
					// TODO - Handle with custom exception
					std::cerr << "Tried to instantiate general_action with owner argument not matching owner\n";
					throw;
				}
			} else {
				input_to_atom.insert({ input.second, arguments[counter] });
			}
			counter++;

		}
		auto condition_owner_to_agent = get_condition_owner_to_agent(domain, input_to_atom);

		return Action(*this, domain.get_agent_id(owner), input_to_atom, condition_owner_to_agent);
	}

	
	bool General_Action::is_correct_type(const std::string& type, const std::string& object, const Domain& domain) const {
		auto type_atoms = domain.get_all_atoms_of_type(type);
		return (find(type_atoms.begin(), type_atoms.end(), object) != type_atoms.end());
	}

	// Copying agents as const Agent& does not seem to play nice with condition_owner_to_agent
	std::unordered_map<std::string, std::vector<Agent>> General_Action::get_condition_owner_to_agent(const Domain& domain, const std::unordered_map<std::string, std::string>& input_to_atom) const{
		std::unordered_map<std::string, std::vector<Agent>> condition_owner_to_agent;
		std::unordered_set<std::string> seen_agents;

		for (auto& edge : edge_conditions) {
			if (edge.first == REST_KEYWORD) {
				condition_owner_to_agent.insert({ edge.first, { } });
			}
			else {
				auto& agent = domain.get_agent(input_to_atom.at(edge.first));
				seen_agents.insert(agent.get_name());
				condition_owner_to_agent.insert({ edge.first, { agent } });
			}
		}

		for (auto& agent : domain.get_agents()) {
			if (seen_agents.find(agent.get_name()) == seen_agents.end()) {
				condition_owner_to_agent[REST_KEYWORD].push_back(agent);
			}
		}

		return std::move(condition_owner_to_agent);
	}
}