#include "Action.hpp"

#include "Agents.hpp"
#include "Domain.hpp"
#include "Formula_Types.hpp"
#include "World.hpp"

namespace del
{

	Action::Action()
		:args(),
		cost(-1),
		name("EMPTY"),
		events(),
		edge_conditions()
	{

	}

	Action::Action(const General_Action& other, const Propositions_Lookup& propositions_lookup, const Atoms& arguments, const Agents& agents)
		:args(arguments),
		cost(other.get_cost()),
		name(other.get_name()),
		events(other, arguments, propositions_lookup, agents),
		edge_conditions(other, propositions_lookup, events, arguments, agents)
	{
		const Atom* owner_atom = arguments.at(other.get_owner().second.id);
		owner = agents.get(owner_atom);
	}

	bool Action::is_condition_fulfilled(const Agent* agent, Event_Id event_from, Event_Id event_to, const State& state, const World* world, const Domain& domain) const
	{
		auto condition = edge_conditions.get_precondition(agent, event_from, event_to);
		if (condition != nullptr)
		{
			return (*condition).valuate(world, domain, state);
		}
		else
		{
			return false;
		}
	}

	std::string Action::to_string() const
	{
		return to_string(0);
	}

	std::string Action::to_string(size_t indentation) const
	{
		return std::string(indentation, '-')
			+ name
			+ "("
			+ args.to_string()
			+ ")";
	}

	std::string Action::to_compact_string() const
	{
		return owner->get_name() + events.to_compact_string();
	}

	size_t Action::get_cost() const
	{
		return cost;
	}

	const Action_Events& Action::get_events() const
	{
		return events;
	}

	const Agent* Action::get_owner() const
	{
		return owner;
	}

	std::string Action::get_name() const
	{
		return name;
	}
}