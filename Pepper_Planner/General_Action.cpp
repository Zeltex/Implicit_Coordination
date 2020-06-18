#include "General_Action.hpp"

namespace del {

	void General_Action::set_owner(std::string agent) {
		owner = agent;
	}

	void General_Action::set_name(std::string name) {
		this->name = name;
	}

	void General_Action::add_event(Action_Event event) {
		events.push_back(event);
	}
}