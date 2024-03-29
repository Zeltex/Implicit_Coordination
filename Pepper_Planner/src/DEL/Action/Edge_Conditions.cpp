#include "Edge_Conditions.hpp"

#include "Action_Events.hpp"
#include "Atoms.hpp"
#include "Converter_Base.hpp"
#include "Converter_Action.hpp"
#include "General_Edge_Conditions.hpp"

#include <cassert>

namespace del
{
	Edge_Conditions::Edge_Conditions()
	{

	}

	Edge_Conditions::Edge_Conditions(size_t agents)
		: conditions() 
	{

	}

	Edge_Conditions::Edge_Conditions(const General_Edge_Conditions& other, const std::map<std::string, Event_Id>& event_name_to_id, const Converter_Base* general_to_instantiated)
	{
		for (const General_Edge_Condition& general_edge_condition : other.edge_conditions)
		{
			assert(event_name_to_id.find(general_edge_condition.event_from) != event_name_to_id.end());
			Event_Id event_from = event_name_to_id.at(general_edge_condition.event_from);
			Event_Id event_to = event_name_to_id.at(general_edge_condition.event_to);

			conditions[event_from][event_to] = Formula(general_edge_condition.condition, general_to_instantiated);
		}
	}

	void Edge_Conditions::insert(Event_Id event_from, Event_Id event_to, Formula&& condition)
	{
		auto it = conditions.find(event_from.id);
		if (it == conditions.end()) {
			conditions.emplace(event_from.id, std::move(std::map<Event_Id, Formula>{}));
		}
		conditions[event_from.id][event_to.id] = std::move(condition);
	}

	const Formula* Edge_Conditions::get_condition(Event_Id event_from, Event_Id event_to) const {
		auto it1 = conditions.find(event_from.id);
		if (it1 == conditions.end())
		{
			return nullptr;
		}

		auto it2 = it1->second.find(event_to.id);
		if (it2 == it1->second.end()) 
		{
			return nullptr;
		}

		return &it2->second;
	}

	Agent_Edge_Conditions::Agent_Edge_Conditions() 
	{

	}

	Agent_Edge_Conditions::Agent_Edge_Conditions(const General_Action& general_action, const Propositions_Lookup& propositions_lookup, const Action_Events& action_events, const Atoms& arguments, const Agents& agents)
		: edge_conditions(agents.size())
	{

		Converter_Action converter_action{ propositions_lookup, general_action.get_inputs(), arguments, agents };
	

		std::map<std::string, Event_Id> event_name_to_id = action_events.get_name_to_id();
		const General_Agent_Edge_Conditions& other = general_action.get_edge_conditions();

		// Find all agents contained in REST_INDEX
		std::set<const Agent*> unseen_agents;
		for (auto& agent : agents)
		{
			unseen_agents.insert(&agent);
		}

		for (const auto& [agent_name, general_edge_conditions] : other.agent_edge_conditions)
		{
			if (agent_name == REST_KEYWORD)
			{
				continue;
			}
			const Agent* agent = converter_action.convert(agent_name);
			assert(unseen_agents.find(agent) != unseen_agents.end());
			unseen_agents.erase(unseen_agents.find(agent));
		}


		for (const auto& [agent_name, general_edge_conditions] : other.agent_edge_conditions)
		{
			if (agent_name == REST_KEYWORD)
			{
				for (const Agent* agent : unseen_agents)
				{
					converter_action.set_rest(agent);
					assert(agent->get_id().id < edge_conditions.size());
					edge_conditions.at(agent->get_id().id) = Edge_Conditions(general_edge_conditions, event_name_to_id, &converter_action);
				}
			}
			else
			{
				converter_action.set_rest(nullptr);
				const Agent* agent = converter_action.convert(agent_name);
				edge_conditions.at(agent->get_id().id) = Edge_Conditions(general_edge_conditions, event_name_to_id, &converter_action);
			}
		}
	}

	const Formula* Agent_Edge_Conditions::get_precondition(Agent_Id agent, Event_Id event_from, Event_Id event_to) const
	{
		return edge_conditions.at(agent.id).get_condition(event_from, event_to);
	}
}