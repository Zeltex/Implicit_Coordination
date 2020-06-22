#include "General_Action.hpp"

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

	const std::vector<std::string>& General_Action::get_designated_events() const {
		return designated_events;
	}

	const std::vector<Action_Event>& General_Action::get_events() const {
		return events;
	}
}