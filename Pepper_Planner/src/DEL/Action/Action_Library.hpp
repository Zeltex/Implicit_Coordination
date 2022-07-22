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
		Action_Library(General_Actions& general_actions, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup, const Agents& agents, const Propositions& rigid_propositions, const State& state, const Domain& domain);

		const std::vector<Action>&	get_actions() const;
		const General_Action&		get_general_action(const std::string& name) const;
		const Action*				get_next_action();
		bool						has_action() const;
		void						load_actions();
	private:

		size_t action_counter;
		std::vector<Action> announce_actions;
		std::vector<Action> actions;
		std::vector<std::unique_ptr<General_Action>> general_actions;
		std::unordered_map<std::string, size_t> general_action_name_to_id;
	};
}