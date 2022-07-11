#include "Action.hpp"

#include "Domain.hpp"
#include "Formula_Types.hpp"
#include "World.hpp"

namespace del {

	Action::Action()
		:args(),
		cost(-1),
		name("EMPTY"),
		events(),
		designated_events(),
		edge_conditions()
	{

	}

	Action::Action(const General_Action& other, const Propositions_Lookup& propositions_lookup, const Atoms& arguments, const Agents& agents)
		:args(arguments), 
		cost(other.get_cost()), 
		name(other.get_name()), 
		events(other, arguments, propositions_lookup),
		designated_events(other, events),
		edge_conditions(other, propositions_lookup, events, arguments, agents)
	{
		const Atom_Id& owner_atom = arguments.at(other.get_owner().second.id).get_id();
		owner = agents.get(owner_atom).get_id();
	}

	bool Action::is_event_designated(Event_Id event) const {
		return designated_events.contains(event);
	}

	bool Action::is_condition_fulfilled(Agent_Id agent, Event_Id event_from, Event_Id event_to, const State& state, const World_Id world, const Domain& domain) const {
		auto condition = edge_conditions.get_precondition(agent, event_from, event_to);
		if (condition != nullptr) 
		{
			return (*condition).valuate(world.id, domain, state);
		} 
		else 
		{
			return false;
		}
	}

	std::string Action::to_string(const Domain& domain) const {
		return to_string(0, domain);
	}

	//std::string Action::to_string(size_t indenation, const Domain& domain) const {
	//	return get_indentation(indenation) 
	//		+ " Action\n(name, " 
	//		+ name 
	//		+ ") (owner, " 
	//		+ std::to_string(owner.id) 
	//		+ ") (Relations size, " 
	//		+ std::to_string(edge_conditions.size()) 
	//		+ ") (Designated events"
	//		+ designated_events.to_string()
	//		+ ")"
	//		+ events.to_string(domain);
	//}

	std::string Action::to_string(size_t indenation, const Domain& domain) const {
		auto output = get_indentation(indenation)
			+ " Action "
			+ name
			+ "(";
		
		bool first = true;
		for (auto& arg : args)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				output += ",";
			}
			output += arg.get_name();
		}

		return output + ")";
	}

	std::string Action::to_compact_string(const Domain& domain) const {
		return std::to_string(owner.id) + events.to_compact_string(domain);
	}

	size_t Action::get_cost() const {
		return cost;
	}

	const Action_Events& Action::get_events() const {
		return events;
	}

	Agent_Id Action::get_owner() const {
		return owner;
	}

	std::string Action::get_name() const {
		return name;
	}
}