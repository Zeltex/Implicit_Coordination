#pragma once

#include <vector>
#include <string>
#include <map>

#include "Types.hpp"
#include "State.hpp"
#include "Formula.hpp"
#include "Action_Events.hpp"
#include "Action.hpp"
#include "Core.hpp"
#include "Proposition_Instance.hpp"
#include "Agents.hpp"
#include "Atoms.hpp"
#include "General_Domain.hpp"

namespace del {
	class General_Agents;
	class Domain {
	public:
		Domain(General_Domain general_domain);
		Domain(State initial_state, const General_Agents& agents) : states({ initial_state }), agents(agents) {}

		const Agent&				get_agent(const Atom_Id& id) const;
		const Agent&				get_agent(const Agent_Id& id) const;
		const Agent&				get_agent(const std::string& name) const;
		const Agents&				get_agents() const;
		const Atoms&				get_all_atoms_of_type(const std::string& type) const;
		const Atom&					get_atom(const std::string& atom_name) const;
		const Atom&					get_atom(const Atom_Id& atom_id) const;
		State						get_current_state() const;
		const Proposition&			get_proposition(const Proposition_Instance& proposition_instance) const;
		const Proposition_Instance&	get_proposition_instance(const Proposition& proposition) const;
		bool						is_rigid(const Proposition& proposition) const;

		void set_objects(const std::unordered_map<std::string, std::unordered_set<std::string>>& objects, const std::unordered_map<std::string, Atom>& name_to_atom);
		void set_rigid_atoms(const Propositions& rigid_atoms);
		void set_proposition_instances(std::map<Proposition_Instance, Proposition>&& instance_to_proposition);
		void add_new_current_state(const State& state);

	private:
		std::vector<State> states;
		Agents agents;
		Propositions rigid_atoms;

		std::map<Proposition_Instance, Proposition> instance_to_proposition;
		std::unordered_map<Proposition, Proposition_Instance> proposition_to_instance;

		// Objects and atoms are same thing, one is just sorted on type (need to rename objects to atoms)
		std::unordered_map<std::string, Atoms> objects;
		std::unordered_map<std::string, Atom> name_to_atom;
		std::unordered_map<size_t, Atom> id_to_atom;
	};
}