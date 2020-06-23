#include "General_Action.hpp"
#include "Action.hpp"
#include "Domain.hpp"

namespace del {

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
		// TODO - Include name
	}

	void General_Action::add_reachability_relation(Agent_Id agent, Event_Id from, Event_Id to) {
		reachability_relation[agent.id].emplace_back(from, to);
	}

	void General_Action::set_amount_of_agents(size_t amount_of_agents) {
		for (size_t i = 0; i < amount_of_agents; i++) {
			reachability_relation.emplace_back();
		}
	}

	const std::vector<std::vector<Event_Relation>>& General_Action::get_reachability_relations() const {
		return reachability_relation;
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

	Action General_Action::create_action(std::string owner, const std::vector<std::string>& arguments, const Domain& domain) const {
		auto owner_type_atoms = domain.get_all_atoms_of_type(this->owner.first);
		if (find(owner_type_atoms.begin(), owner_type_atoms.end(), owner) == owner_type_atoms.end()) {
			// TODO - Handle with custom exception
			std::cerr << "Tried to instantiate general_action with owner of wrong type\n";
			throw;
		}

		std::unordered_map<std::string, std::string> input_to_atom;
		size_t counter = 0;
		for (auto& input : inputs) {
			if (input.second == this->owner.second && owner != arguments[counter]) {
				// TODO - Handle with custom exception
				std::cerr << "Tried to instantiate general_action with owner argument not matching owner\n";
				throw;
			}
			
			auto& atoms = domain.get_all_atoms_of_type(input.first);
			if (find(atoms.begin(), atoms.end(), arguments[counter]) == atoms.end()) {
				// TODO - Handle with custom exception
				std::cerr << "Tried to instantiate general_action with argument of wrong type\n";
				throw;
			}
			input_to_atom[input.second] = arguments[counter];
			counter++;
		}
		return Action(*this, domain.get_agent_id(owner), input_to_atom);
	}
}