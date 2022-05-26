#pragma once

#include <vector>
#include <string>
#include <map>

#include "Action_Library.hpp"
#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Formula.hpp"
#include "Propositions_Lookup.hpp"
#include "State.hpp"


namespace del {
	class General_Agents;
	class General_Domain;
	class Proposition_Instance;

	class Domain {
	public:
		Domain(const General_Domain& general_domain);

		void						add_new_current_state(const State& state);
		const Agent&				get_agent(const Atom_Id& id) const;
		const Agent&				get_agent(const Agent_Id& id) const;
		const Agent&				get_agent(const std::string& name) const;
		const Agents&				get_agents() const;
		const Atoms&				get_atoms(const std::string& type) const;
		const Atom&					get_atom(const std::string& atom_name) const;
		const Atom&					get_atom(const Atom_Id& atom_id) const;
		State						get_current_state() const;
		const Proposition&			get_proposition(const Proposition_Instance& proposition_instance) const;
		const Proposition_Instance&	get_proposition_instance(const Proposition& proposition) const;
		const Propositions_Lookup&	get_propositions_lookup() const;
		bool						is_rigid(const Proposition& proposition) const;

		const Atom_Lookup&			get_atom_lookup() const;

	private:
		// The initializer list dependens on this order
		Agents agents;
		Atom_Lookup atom_lookup;
		Propositions_Lookup propositions_lookup;
		std::vector<State> states;
		Formula goal;
		Propositions rigid_propositions;
		Action_Library action_library;

	};
}