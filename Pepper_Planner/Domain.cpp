#include "Domain.hpp"

#include "Core.hpp"
#include "General_Domain.hpp"
#include "State.hpp"

namespace del 
{

	Domain::Domain(const General_Domain& general_domain)
		: agents(general_domain.agents),
		atom_lookup(general_domain.objects),
		propositions_lookup(general_domain.typed_propositions, atom_lookup),
		states(1, State{ general_domain.state, propositions_lookup }),
		rigid_propositions(general_domain.rigid_propositions, propositions_lookup),
		action_library(general_domain.actions, propositions_lookup, atom_lookup)

	{
		auto converter = general_domain.proposition_instance_buffer.create_converter(propositions_lookup);

		goal = Formula(general_domain.goal, converter);

	}

	void Domain::add_new_current_state(const State& state) 
	{
		states.push_back(state);
	}

	State Domain::get_current_state() const {
		return states.back();
	}

	const Agents& Domain::get_agents() const {
		return agents;
	}

	const Agent& Domain::get_agent(const std::string& name) const {
		return agents.get(name);
	}

	const Agent& Domain::get_agent(const Agent_Id& id) const {
		return agents.get(id);
	}

	const Agent& Domain::get_agent(const Atom_Id& id) const {
		return get_agent(get_atom(id).get_name());
	}

	const Atoms& Domain::get_atoms(const std::string& type) const {
		return atom_lookup.get_atoms(type);
	}

	const Atom& Domain::get_atom(const Atom_Id& atom_id) const {
		return  atom_lookup.get_atom(atom_id.id);
	}

	const Atom& Domain::get_atom(const std::string& atom_name) const {
		return atom_lookup.get_atom(atom_name);
	}

	const Proposition& Domain::get_proposition(const Proposition_Instance& proposition_instance) const {
		return propositions_lookup.get(proposition_instance);
	}

	const Proposition_Instance& Domain::get_proposition_instance(const Proposition& proposition) const {
		return propositions_lookup.get_instance(proposition);
	}

	const Propositions_Lookup& Domain::get_propositions_lookup() const
	{
		return propositions_lookup;
	}

	bool Domain::is_rigid(const Proposition& proposition) const
	{
		return rigid_propositions.contains(proposition);
	}
}