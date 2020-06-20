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


	void General_Action::create_event(std::string name, Formula&& preconditions, std::unordered_set<std::string> add_list, std::unordered_set<std::string> delete_list) {
		events.emplace_back(Event_Id{ events.size() }, std::move(preconditions), add_list, delete_list);
		// TODO - Include name
	}
}