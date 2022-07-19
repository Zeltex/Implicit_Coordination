#pragma once
#include <vector>
#include <map>
#include <optional>

#include "General_Actions.hpp"
#include "General_Edge_Conditions.hpp"

namespace del
{
	class Action_Events;
	class Agent;
	class Converter_Base;
	class Domain;
	class Propositions_Lookup;

	struct Edge_Conditions {
		Edge_Conditions();
		Edge_Conditions(size_t agents);
		Edge_Conditions(const General_Edge_Conditions& other, const std::map<std::string, Event_Id>& event_name_to_id, const Converter_Base* general_to_instantiated);

		void insert(Event_Id event_from, Event_Id event_to, Formula&& condition);
		const Formula* get_condition(Event_Id event_from, Event_Id event_to) const;
		std::map<Event_Id, std::map<Event_Id, Formula>> conditions;
	private:
	};

	class Agent_Edge_Conditions
	{
	public:
		Agent_Edge_Conditions();
		Agent_Edge_Conditions(const General_Action& general_action, const Propositions_Lookup& propositions_Lookup, const Action_Events& action_events, const Atoms& arguments, const Agents& agents);
		const Formula* get_precondition(const Agent* agent, Event_Id event_from, Event_Id event_to) const;
	private:
		std::vector<Edge_Conditions> edge_conditions;
	};
}