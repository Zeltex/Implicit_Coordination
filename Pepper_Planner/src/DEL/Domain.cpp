#include "Domain.hpp"

#include <assert.h>

#include "Core.hpp"
#include "General_Domain.hpp"
#include "Propositions_Lookup.hpp"
#include "State.hpp"


namespace del 
{

	Domain::Domain(std::unique_ptr<General_Domain> general_domain)
		: agents(general_domain->agents),
		atom_lookup(general_domain->objects),
		propositions_lookup(general_domain->typed_propositions, atom_lookup, general_domain->state, general_domain->rigid_propositions),
		states(1, State{ general_domain->state, propositions_lookup, agents }),
		rigid_propositions(general_domain->rigid_propositions, propositions_lookup),
		action_library(general_domain->actions, propositions_lookup, atom_lookup, agents, rigid_propositions, states.front(), *this)

	{
		Converter converter = general_domain->proposition_instance_buffer.create_converter(propositions_lookup);

		// For the goal formula, the correct agent_id's are already used, so map to self
		for (const auto& agent : agents)
		{
			converter.set(agent.get_id(), agent.get_id());
		}

		goal = Formula(general_domain->goal, converter);

	}

	void Domain::add_new_current_state(const State& state) 
	{
		states.push_back(state);
	}

	const State& Domain::get_current_state() const {
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

	const Atom_Lookup& Domain::get_atom_lookup() const
	{
		return atom_lookup;
	}

	bool Domain::is_rigid(const Proposition& proposition) const
	{
		return rigid_propositions.contains(proposition);
	}

	Action_Library& Domain::get_action_library()
	{
		return action_library;
	}

	const Formula& Domain::get_goal() const
	{
		return goal;
	}

	void Domain::perform_action(const Action* action)
	{
		const State& current_state = get_current_state();
		// TODO - Handle an inapplicable action here
		std::optional<State> product_update = current_state.product_update(action, *this);
		assert(product_update.has_value());
		
		product_update.value().contract();
		add_new_current_state(product_update.value());
		PRINT_ACTION_TO_CONSOLE(action, *(this));
	}

	void Domain::perform_action(const std::string& name, const std::vector<std::string>& arguments)
	{
		Atoms temp_arguments;
		temp_arguments.reserve(arguments.size());
		for (auto& argument : arguments) {
			temp_arguments.insert(get_atom(argument));
		}

		auto action = Action(action_library.get_general_action(name), propositions_lookup, temp_arguments, agents);
		perform_action(&action);
	}

}