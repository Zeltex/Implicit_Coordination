#pragma once

#include <algorithm>
#include <vector>
#include <string>
#include <unordered_map>

#include "Formula.hpp"
#include "Formula_Types.hpp"
#include "Action_Event.hpp"
#include "Misc.hpp"
#include "Types.hpp"
#include "General_Action.hpp"
#include "Agent.hpp"


namespace del {
	class World;
	class State;
	class Action {
	public:
		Action() {}
		Action(Agent_Id owner, size_t number_of_agents);
		Action(const General_Action& general_action, const Domain& domain, const std::vector<Atom_Id>& arguments);

		void add_designated_event(Event_Id event);
		void add_event(const Action_Event& event);
		void add_event(const std::string& name, Event_Id id, Formula&& precondition, std::vector<Proposition>&& proposition_add, std::vector<Proposition>&& proposition_delete);
		void add_reachability(Agent_Id owner, Event_Id event_from, Event_Id event_to, Formula&& condition);
		void set_cost(size_t cost);
		void set_name(const std::string& name);

		size_t								get_cost() const;
		const std::vector<Action_Event>&	get_events() const;
		std::string							get_name() const;
		Agent_Id							get_owner() const;

		bool is_event_designated(Event_Id event) const;
		bool is_condition_fulfilled(Agent_Id agent, Event_Id event_from, Event_Id event_to, const State& state, const World_Id world, const Domain& domain) const;


		std::string to_string(const Domain& domain) const;
		std::string to_string(size_t indentation, const Domain& domain) const;
		std::string to_compact_string(const Domain& domain) const;
		std::string to_graph(const std::string& base_id, const Domain& domain) const;

		// Args is mainly debug
		std::vector<Atom_Id> args;

	private:
		void copy_and_instantiate_edge_conditions(const General_Action& general_action, const std::unordered_map<size_t, std::vector<Agent>>& condition_owner_to_id, const std::unordered_map<std::string, Event_Id>& event_name_to_id, const std::vector<Atom_Id>& arguments);
		void copy_and_instantiate_designated_events(const General_Action& general_action, const std::unordered_map<std::string, Event_Id>& event_name_to_id);
		std::unordered_map<std::string, Event_Id> copy_and_instantiate_events(const General_Action& general_action, const std::vector<Atom_Id>& arguments, const Domain& domain);

		std::string get_string(const std::vector<Proposition>& propositions, const Domain& domain) const;

		size_t cost;
		std::vector<Action_Event> events;
		std::vector<Event_Id> designated_events;
		Agent_Id owner;
		std::string name;
		std::vector<Agent_Edges> edge_conditions;

	};
}