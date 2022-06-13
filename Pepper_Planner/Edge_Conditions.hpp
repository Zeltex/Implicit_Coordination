#pragma once
#include <vector>
#include <map>
#include <optional>

#include "General_Actions.hpp"
#include "General_Edge_Conditions.hpp"

namespace del
{
	class Action_Events;
	class Converter;
	class Domain;
	class Propositions_Lookup;

	struct Edge_Conditions {
		Edge_Conditions();
		Edge_Conditions(const General_Edge_Conditions& other, const std::map<std::string, Event_Id>& event_name_to_id, const Converter& general_to_instantiated);

		Edge_Conditions(size_t agents) : conditions(), current_size(0) {}
		void insert(Event_Id event_from, Event_Id event_to, Formula&& condition);
		std::optional<const Formula*> get_condition(Event_Id event_from, Event_Id event_to) const;
		size_t size() const;

		std::map<Event_Id, std::map<Event_Id, Formula>> conditions;
	private:
		size_t current_size;
	};

	class Agent_Edge_Conditions
	{
	public:
		Agent_Edge_Conditions();
		Agent_Edge_Conditions(const General_Action& general_action, const Propositions_Lookup& propositions_Lookup, const Action_Events& action_events, const Atoms& arguments, const Agents& agents);
		std::optional<const Formula*> get_precondition(Agent_Id agent, Event_Id event_from, Event_Id event_to) const;
		size_t size() const;
	private:
		std::vector<Edge_Conditions> edge_conditions;
	};
}