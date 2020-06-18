#pragma once

#include <string>

#include "Action_Event.hpp"

namespace del {
	class General_Action {
	public:
		General_Action() {}
		void set_owner(std::string agent);
		void set_name(std::string name);
		void add_event(Action_Event event);
	private:

		std::string name;
		std::string owner;
		std::vector<Action_Event> events;
	};
}