#include "Action_Library.hpp"

#include "Core.hpp"
#include "Domain.hpp"
#include "General_Actions.hpp"

namespace del {

	Action_Library::Action_Library(): 
		action_counter(0), 
		announce_enabled(false), 
		actions() {
	}

	Action_Library::Action_Library(const General_Actions& general_actions, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup)
		: action_counter(0), 
		announce_enabled(false), 
		actions() 
	{
		for (const General_Action& general_action : general_actions)
		{
			add_general_action(general_action, propositions_lookup, atom_lookup);
		}
	}


	void Action_Library::load_actions(const State& state, const Domain& domain) {
		// TODO - These actions should be saved in a map so that each action is only generated once
		//announce_actions = std::move(get_announce_actions(state, domain));
		action_counter = 0;
	}

	bool Action_Library::has_action() const {
		return action_counter < actions.size() + announce_actions.size();
	}

	const Action& Action_Library::get_next_action() {
		size_t temp_counter = action_counter++;
		if (temp_counter < actions.size()) {
			return actions.at(temp_counter);
		} else {
			return announce_actions.at(temp_counter - actions.size());
		}
	}

	const std::vector<Action>& Action_Library::get_actions() const{
		return actions;
	}

	const General_Action& Action_Library::get_general_action(const std::string& name) const {
		return general_actions.at(general_action_name_to_id.at(name));
	}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}

	void Action_Library::add_general_action(const General_Action& general_action, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup) {

		general_action_name_to_id[general_action.get_name()] = general_actions.size();
		general_actions.push_back(general_action);

		std::vector<std::vector<Atom>> atoms;
		std::vector<size_t> counters;

		// Load all combinations of input
		for (auto& entry : general_action.get_inputs()) {
			const Atoms& temp = atom_lookup.get_atoms(entry.get_type());
			atoms.emplace_back(temp.begin(), temp.end());
			counters.emplace_back(0);
		}

		// Generate all possible valid inputs
		bool done = false;
		while (!done) {

			Atoms arguments;
			for (size_t i = 0; i < counters.size(); i++) {
				arguments.insert(atoms[i][counters[i]]);
			}
			actions.emplace_back(general_action, propositions_lookup, arguments);

			// Advance indices
			size_t index = 0;
			while (!done && ++counters.at(index) >= atoms.at(index).size()) {
				counters.at(index++) = 0;
				done = index >= counters.size();
			}
		}
	}
}