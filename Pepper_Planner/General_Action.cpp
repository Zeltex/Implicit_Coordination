#include "General_Action.hpp"

namespace del {

	void General_Action::set_owner(std::string agent) {
		owner = agent;
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

	const std::vector<std::pair<std::string, std::string>>& General_Action::get_inputs() const {
		return inputs;
	}

	std::string General_Action::get_owner() const{
		return owner;
	}

	const std::vector<std::string>& General_Action::get_designated_events() const {
		return designated_events;
	}

	const std::vector<Action_Event>& General_Action::get_events() const {
		return events;
	}
}