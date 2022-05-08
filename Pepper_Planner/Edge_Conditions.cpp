#include "Edge_Conditions.hpp"
#include "General_Edge_Conditions.hpp"
#include "Action_Events.hpp"
#include "Atoms.hpp"

namespace del
{
	Edge_Conditions::Edge_Conditions()
	{

	}

	Edge_Conditions::Edge_Conditions(const General_Edge_Conditions& other, const std::map<std::string, Event_Id>& event_name_to_id, const std::map<Proposition, Proposition>& general_to_instantiated)
	{
		for (const General_Edge_Condition& general_edge_condition : other.edge_conditions)
		{
			Event_Id event_from = event_name_to_id.at(general_edge_condition.event_from);
			Event_Id event_to = event_name_to_id.at(general_edge_condition.event_to);
			conditions[event_from][event_to] = Formula(general_edge_condition.condition, general_to_instantiated);
		}
	}

	void Edge_Conditions::insert(Event_Id event_from, Event_Id event_to, Formula&& condition) {
		auto it = conditions.find(event_from.id);
		if (it == conditions.end()) {
			conditions.insert({ event_from.id, {} });
		}
		conditions[event_from.id][event_to.id] = std::move(condition);

		// TODO - Only increment if condition not already set
		current_size++;
	}

	std::optional<const Formula*> Edge_Conditions::get_condition(Event_Id event_from, Event_Id event_to) const {
		auto it1 = conditions.find(event_from.id);
		if (it1 != conditions.end()) {
			auto it2 = it1->second.find(event_to.id);
			if (it2 != conditions.at(event_from.id).end()) {
				return { &(it2->second) };
			}
		}
		return {};
	}

	size_t Edge_Conditions::size() const {
		return this->current_size;
	}

	Agent_Edge_Conditions::Agent_Edge_Conditions() 
	{

	}

	Agent_Edge_Conditions::Agent_Edge_Conditions(const General_Action& general_action, const Domain& domain, const Action_Events& action_events, const Atoms& arguments)
		: edge_conditions(general_action.get_edge_conditions().size())
	{
		std::map<std::string, Event_Id> event_name_to_id = action_events.get_name_to_id();
		const General_Agent_Edge_Conditions& other = general_action.get_edge_conditions();
		Atoms converted_arguments = arguments;

		for (const auto& [agent_atom, general_edge_conditions] : other.agent_edge_conditions)
		{
			for (const Agent& agent : other.atom_to_agent.at(agent_atom))
			{
				if (agent_atom == REST_INDEX) 
				{
					converted_arguments.set(REST_INDEX, { agent.get_atom_id().id }); // TODO - Janky conversion, need a better 
				}
				std::map<Proposition, Proposition> general_to_instantiated = general_action.create_converter(domain, converted_arguments);

				edge_conditions.at(agent.get_id().id) = Edge_Conditions(general_edge_conditions, event_name_to_id, general_to_instantiated);
			}
		}
	}

	std::optional<const Formula*> Agent_Edge_Conditions::get_precondition(Agent_Id agent, Event_Id event_from, Event_Id event_to) const
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