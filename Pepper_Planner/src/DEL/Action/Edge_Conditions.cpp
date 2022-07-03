#include "Edge_Conditions.hpp"

#include "Action_Events.hpp"
#include "Atoms.hpp"
#include "Atom_Arguments.hpp"
#include "Converter.hpp"
#include "General_Edge_Conditions.hpp"

#include <cassert>

namespace del
{
	Edge_Conditions::Edge_Conditions()
	{

	}

	Edge_Conditions::Edge_Conditions(const General_Edge_Conditions& other, const std::map<std::string, Event_Id>& event_name_to_id, const Converter& general_to_instantiated)
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

		// TODO - Only increment if condition not already set
		current_size++;
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

	size_t Edge_Conditions::size() const {
		return this->current_size;
	}

	Agent_Edge_Conditions::Agent_Edge_Conditions() 
	{

	}

	Agent_Edge_Conditions::Agent_Edge_Conditions(const General_Action& general_action, const Propositions_Lookup& propositions_Lookup, const Action_Events& action_events, const Atoms& arguments, const Agents& agents)
		: edge_conditions(agents.size())
	{
		std::map<std::string, Event_Id> event_name_to_id = action_events.get_name_to_id();
		const General_Agent_Edge_Conditions& other = general_action.get_edge_conditions();
		Atom_Arguments converted_arguments = arguments;

		// Find all agents contained in REST_INDEX
		std::set<Agent> unseen_agents { agents.get_all().begin(), agents.get_all().end() };
		for (const auto& [agent_atom, general_edge_conditions] : other.agent_edge_conditions)
		{
			if (agent_atom == REST_INDEX)
			{
				continue;
			}

			Atom atom = arguments.at(agent_atom);
			Agent agent = agents.get(atom.get_id());
			assert(unseen_agents.find(agent) != unseen_agents.end());
			unseen_agents.erase(unseen_agents.find(agent));
		}


		for (const auto& [agent_atom, general_edge_conditions] : other.agent_edge_conditions)
		{
			if (agent_atom == REST_INDEX)
			{
				for (const Agent& agent : unseen_agents)
				{
					converted_arguments.set(REST_INDEX, agent.get_atom_id());
					Converter general_to_instantiated = general_action.create_converter(propositions_Lookup, converted_arguments);
					assert(agent.get_id().id < edge_conditions.size());
					edge_conditions.at(agent.get_id().id) = Edge_Conditions(general_edge_conditions, event_name_to_id, general_to_instantiated);
				}
			}
			else
			{
				Atom atom = arguments.at(agent_atom);
				Agent agent = agents.get(atom.get_id());
				Converter general_to_instantiated = general_action.create_converter(propositions_Lookup, converted_arguments);

				edge_conditions.at(agent.get_id().id) = Edge_Conditions(general_edge_conditions, event_name_to_id, general_to_instantiated);
			}
		}
	}

	const Formula* Agent_Edge_Conditions::get_precondition(Agent_Id agent, Event_Id event_from, Event_Id event_to) const
	{
		return edge_conditions.at(agent.id).get_condition(event_from, event_to);
	}

	size_t Agent_Edge_Conditions::size() const
	{
		size_t size = 0;
		for (const Edge_Conditions& conditions : edge_conditions) {
			size += conditions.size();
		}
		return size;
	}
}