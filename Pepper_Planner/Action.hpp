#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

#include "Formula.hpp"
#include "Formula_Types.hpp"
#include "Action_Events.hpp"
#include "Misc.hpp"
#include "Types.hpp"
#include "General_Action.hpp"
#include "Agent.hpp"
#include "Edge_Conditions.hpp"
#include "Action_Events.hpp"
#include "Designated_Events.hpp"


namespace del {

	class World;
	class State;
	class Action {
	public:
		Action();
		Action(const General_Action& general_action, const Domain& domain, const std::vector<Atom_Id>& arguments);

		size_t					get_cost() const;
		const Action_Events&	get_events() const;
		std::string				get_name() const;
		Agent_Id				get_owner() const;

		bool is_event_designated(Event_Id event) const;
		bool is_condition_fulfilled(Agent_Id agent, Event_Id event_from, Event_Id event_to, const State& state, const World_Id world, const Domain& domain) const;


		std::string to_string(const Domain& domain) const;
		std::string to_string(size_t indentation, const Domain& domain) const;
		std::string to_compact_string(const Domain& domain) const;

		// Args is mainly debug
		std::vector<Atom_Id> args;

	private:
		size_t cost;
		// Events must be above designated_events and edge_conditions, for the initializer list ordering
		Action_Events events;
		Designated_Events designated_events;
		Agent_Id owner;
		std::string name;
		Agent_Edge_Conditions edge_conditions;

	};
}