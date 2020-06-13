#pragma once

#include <vector>
#include <string>

#include "Formula.hpp"
#include "Action_Event.hpp"

namespace del {
	class Action {
	public:
		Action() = delete;
		Action(Agent_Id owner, size_t number_of_agents);
		void add_event(const Action_Event& event);
		void add_event(Event_Id id, Formula&& precondition, std::unordered_set<std::string>&& proposition_add, std::unordered_set<std::string>&& proposition_delete);
		std::vector<Action_Event>& get_events();
		Agent_Id get_owner();
		bool is_one_reachable(Event_Id world1, Event_Id world2, Agent_Id agent);
		bool is_event_designated(Event_Id event) const;

	private:
		std::vector<Action_Event> events;
		std::vector<Event_Id> designated_events;
		std::vector<std::vector<Event_Relation>> indistinguishability_relation;
		Agent_Id owner;

	};
}