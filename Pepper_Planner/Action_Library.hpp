#pragma once

#include <vector>
#include <iostream>

#include "General_Actions.hpp"
#include "Action.hpp"
#include "Agents.hpp"

namespace del {
	class Atom_Lookup;
	class Domain;
	class Propositions_Lookup;

	class Action_Library {
	public:
		Action_Library();
		Action_Library(const General_Actions& general_actions, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup, const Agents& agents);
		const std::vector<Action>& get_actions() const;
		const General_Action& get_general_action(const std::string& name) const;
		void add_action(const Action& action);

		void load_actions(const State& state, const Domain& domain);
		bool has_action() const;
		const Action& get_next_action();
	private:
		void add_general_action(const General_Action& action, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup, const Agents& agents);

		size_t action_counter;

		bool announce_enabled;

		std::vector<Action> announce_actions;
		std::vector<Action> actions;
		std::vector<General_Action> general_actions;
		std::unordered_map<std::string, size_t> general_action_name_to_id;
	};
}