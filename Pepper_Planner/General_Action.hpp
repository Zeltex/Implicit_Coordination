#pragma once

#include <string>
#include <unordered_set>

#include "Action_Event.hpp"

namespace del {
	class General_Action {
	public:
		General_Action() {}
		void set_owner(std::string agent);
		void set_name(std::string name);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_action_input(std::vector<std::pair<std::string, std::string>> inputs);
		void create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list);

	private:

		std::string name;
		std::string owner;
		std::vector<Action_Event> events;
		std::vector<std::string> designated_events;
		std::vector<std::pair<std::string, std::string>> inputs;
	};
}