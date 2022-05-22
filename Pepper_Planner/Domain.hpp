#pragma once

#include <vector>
#include <string>
#include <map>

#include "Action.hpp"
#include "Action_Library.hpp"
#include "Action_Events.hpp"
#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Core.hpp"
#include "Formula.hpp"
#include "General_Domain.hpp"
#include "Proposition_Instance.hpp"
#include "Propositions_Lookup.hpp"
#include "State.hpp"
#include "Types.hpp"


namespace del {
	class General_Domain;
	class General_Agents;
	class Domain {
	public:
		Domain(const General_Domain& general_domain);
		//Domain(State initial_state, const General_Agents& agents);

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


		//void set_objects(const std::unordered_map<std::string, std::unordered_set<std::string>>& type_to_atom, const std::unordered_map<std::string, Atom>& name_to_atom);
		//void set_rigid_atoms(const Propositions& rigid_propositions);
		//void set_proposition_instances(std::map<Proposition_Instance, Proposition>&& instance_to_proposition);
		void add_new_current_state(const State& state);

	private:
		// NOTE: Don't change the order, initializer list is dependent on it
		Agents agents;
		Atom_Lookup atom_lookup;
		Propositions_Lookup propositions_lookup;
		std::vector<State> states;
		Formula goal;
		Propositions rigid_propositions;
		Action_Library action_library;

	};
}