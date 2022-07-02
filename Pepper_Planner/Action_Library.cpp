#include "Action_Library.hpp"

#include "Core.hpp"
#include "Domain.hpp"
#include "General_Actions.hpp"

#include <assert.h>

namespace del {

	Action_Library::Action_Library(): 
		action_counter(0), 
		announce_enabled(false), 
		actions() {
	}

	Action_Library::Action_Library(const General_Actions& general_actions_in, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup, const Agents& agents, const Propositions& rigid_propositions, const State& state, const Domain& domain)
		: action_counter(0), 
		announce_enabled(false), 
		actions() 
	{
		std::list<Action> actions_to_check;

		Propositions all_propositions = rigid_propositions;
		for (const World& world : state.get_worlds())
		{
			all_propositions.insert(world.get_true_propositions());
		}

		for (const General_Action& general_action : general_actions_in)
		{
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
				Action action{ general_action, propositions_lookup, arguments, agents };
				actions_to_check.push_back(action);


				// Advance indices
				size_t index = 0;
				assert(index < counters.size() && index < atoms.size());
				while (!done && ++counters.at(index) >= atoms.at(index).size()) {
					counters.at(index++) = 0;
					done = index >= counters.size();
					assert(done || (index < counters.size() && index < atoms.size()));
				}
			}

		}

		// Prune actions which are guaranteed to never be applicable
		std::vector<Action> plausible_actions;
		size_t prev_size = -1;
		while (plausible_actions.size() != prev_size)
		{
			prev_size = plausible_actions.size();

			for (auto it = actions_to_check.begin(); it != actions_to_check.end();)
			{
				const Action& action = *it;
				bool found_event = false;

				for (const auto& _event : action.get_events())
				{
					if (_event.get_preconditions().valuate_plausability(all_propositions))
					{
						found_event = true;
						break;
					}
				}

				if (found_event)
				{

					for (const Action_Event& _event : action.get_events())
					{
						all_propositions.insert(_event.get_add_list());
					}

					plausible_actions.push_back(*it);
					it = actions_to_check.erase(it);
				}
				else
				{
					++it;
				}
			}
		}

		actions = std::move(plausible_actions);
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

	const General_Action& Action_Library::get_general_action(const std::string& name) const 
	{
		assert(general_action_name_to_id.find(name) != general_action_name_to_id.end());
		return general_actions.at(general_action_name_to_id.at(name));
	}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}
}