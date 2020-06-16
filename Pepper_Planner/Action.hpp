#pragma once

#include <vector>
#include <string>

#include "Formula.hpp"
#include "Action_Event.hpp"
#include "Misc.hpp"

namespace del {
	class Action {
	public:
		Action() = delete;
		Action(Agent_Id owner, size_t number_of_agents);
		void add_event(const Action_Event& event);
		void add_event(Event_Id id, Formula&& precondition, std::unordered_set<std::string>&& proposition_add, std::unordered_set<std::string>&& proposition_delete);
		const std::vector<Action_Event>& get_events() const;
		Agent_Id get_owner() const;
		bool is_one_reachable(Agent_Id agent, Event_Id world1, Event_Id world2) const;
		bool is_event_designated(Event_Id event) const;
		void add_indistinguishability_relation(Agent_Id agent, Event_Id event_from, Event_Id event_to);
		void add_designated_event(Event_Id event);

		std::string to_string() const;
		std::string to_string(size_t indentation) const;
		std::string to_compact_string() const;

	private:
		std::vector<Action_Event> events;
		std::vector<Event_Id> designated_events;
		std::vector<std::vector<Event_Relation>> indistinguishability_relation;
		Agent_Id owner;

	};
}