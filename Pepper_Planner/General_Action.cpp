#include "General_Action.hpp"
#include "Action.hpp"
#include "Domain.hpp"
#include "Formula_Core.hpp"

namespace del {

	void General_Action::set_cost(size_t cost) {
		this->cost = cost;
	}

	void General_Action::set_owner(std::string type, Atom_Id name) {
		owner = { type, name };
	}

	void General_Action::set_name(std::string name) {
		this->name = name;
	}

	void General_Action::set_designated_events(std::vector<std::string> designated_events) {
		this->designated_events = designated_events;
	}

	void General_Action::set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) {
		this->inputs = inputs;
	}

	void General_Action::create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list) {
		events.emplace_back(name, Event_Id{ events.size() }, std::move(preconditions), add_list, delete_list);
	}

	void General_Action::add_edge_condition(Atom_Id agent, std::vector<Edge_Condition>&& edge_conditions_input) {
		edge_conditions.insert({ agent.id, std::move(edge_conditions_input) });
	} 

	void General_Action::set_amount_of_agents(size_t amount_of_agents) {
		//TODO - Might not be needed anymore
	}

	size_t General_Action::get_cost() const {
		return cost;
	}


	const std::vector<std::pair<std::string, std::string>>& General_Action::get_inputs() const {
		return inputs;
	}

	std::pair<std::string, Atom_Id> General_Action::get_owner() const{
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

	const std::unordered_map<size_t, std::vector<Edge_Condition>>& General_Action::get_edge_conditions() const {
		return edge_conditions;
	}

	Action General_Action::create_action(Atom_Id owner, const std::vector<Atom_Id>& arguments, const Domain& domain) const {

		if (!is_correct_type(this->owner.first, owner, domain)) {
			// TODO - Handle with custom exception
			std::cerr << "Tried to instantiate general_action with owner of wrong type\n";
			exit(-1);
		}
		std::unordered_map<size_t, size_t> input_to_agent;
		std::unordered_map<size_t, Atom_Id> input_to_atom;
		input_to_atom.insert({ this->owner.second.id, owner });

		for (size_t i = 0; i < inputs.size(); ++i) {
			auto& input = inputs[i];
			auto& argument = arguments[i];
			if (!is_correct_type(input.first, argument, domain)) {
				// TODO - Handle with custom exception
				std::cerr << "Tried to instantiate general_action with argument of wrong type\n";
				exit(-1);
			}

			if (i == this->owner.second.id) {
				if (owner != argument) {
					// TODO - Handle with custom exception
					std::cerr << "Tried to instantiate general_action with owner argument not matching owner\n";
					exit(-1);
				}
			} else {
				input_to_atom.insert({ i, argument });
				auto agent_id = domain.get_agent_id_optional(argument);
				if (agent_id.has_value()) {
					input_to_agent[argument.id] = agent_id.value().id;
				}
			}
		}
		auto condition_owner_to_agent = get_condition_owner_to_agent(domain, input_to_atom);

		return Action(*this, domain.get_agent_id(owner), input_to_atom, input_to_agent, condition_owner_to_agent);
	}

	
	bool General_Action::is_correct_type(const std::string& type, const Atom_Id& object, const Domain& domain) const {
		auto type_atoms = domain.get_all_atoms_of_type(type);
		return (find(type_atoms.begin(), type_atoms.end(), object.id) != type_atoms.end());
	}

	// Copying agents as const Agent& does not seem to play nice with condition_owner_to_agent
	std::unordered_map<size_t, std::vector<Agent>> General_Action::get_condition_owner_to_agent(const Domain& domain, const std::unordered_map<size_t, Atom_Id>& input_to_atom) const{
		std::unordered_map<size_t, std::vector<Agent>> condition_owner_to_agent;
		std::unordered_set<std::string> seen_agents;

		for (auto& edge : edge_conditions) {
			if (edge.first == REST_INDEX) {
				condition_owner_to_agent.insert({ REST_INDEX, { } });
			}
			else {
				auto& agent = domain.get_agent_from_atom(input_to_atom.at(edge.first));
				seen_agents.insert(agent.get_name());
				condition_owner_to_agent.insert({ edge.first, { agent } });
			}
		}

		for (auto& agent : domain.get_agents()) {
			if (seen_agents.find(agent.get_name()) == seen_agents.end()) {
				condition_owner_to_agent[REST_INDEX].push_back(agent);
			}
		}

		return std::move(condition_owner_to_agent);
	}
}