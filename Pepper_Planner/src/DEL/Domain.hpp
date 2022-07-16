#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Action_Library.hpp"
#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Converter_Problem.hpp"
#include "Formula.hpp"
#include "Propositions_Lookup.hpp"
#include "State.hpp"


namespace del {
	class General_Agents;
	class General_Domain;
	struct Proposition_Instance;

	class Domain {
	public:
		Domain(std::unique_ptr<General_Domain> general_domain);

		void						add_new_current_state(const State& state);
		Action_Library&				get_action_library(); // TODO - Check if this can be made const
		const Agent*				get_agent(size_t index) const;
		const Agent*				get_agent(Agent_Id id) const;
		const Agent*				get_agent(const std::string& name) const;
		const Agents*				get_agents() const;
		const Atoms*				get_atoms(const std::string& type) const;
		const Atom*					get(const std::string& atom_name) const;
		const State&				get_current_state() const;
		const Formula&				get_goal() const;
		const Propositions_Lookup&	get_propositions_lookup() const;
		bool						is_rigid(const Proposition_Instance* proposition) const;

		const Atom_Lookup&			get_atom_lookup() const;
		void						perform_action(const std::string& name, const std::vector<std::string>& arguments);
		void						perform_action(const Action* action);
	private:
		// The initializer list dependens on this order
		Atom_Lookup atom_lookup;
		Agents agents;
		Propositions_Lookup propositions_lookup;
		Converter_Problem converter_problem;
		std::vector<State> states;
		Formula goal;
		Propositions rigid_propositions;
		Action_Library action_library;

	};
}