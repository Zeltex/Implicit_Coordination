#include "Domain.hpp"

#include <assert.h>

#include "Core.hpp"
#include "General_Domain.hpp"
#include "Propositions_Lookup.hpp"
#include "State.hpp"


namespace del
{

	Domain::Domain(std::unique_ptr<General_Domain> general_domain)
		:
		atom_lookup(general_domain->objects),
		agents(general_domain->agents, atom_lookup),
		propositions_lookup(general_domain->typed_propositions, atom_lookup, general_domain->state, general_domain->rigid_propositions),
		converter_problem(propositions_lookup, atom_lookup, agents),
		states(1, State{ general_domain->state, propositions_lookup, agents, atom_lookup }),
		rigid_propositions(general_domain->rigid_propositions, &converter_problem),
		action_library(general_domain->actions, propositions_lookup, atom_lookup, agents, rigid_propositions, states.front(), *this),
		goal(general_domain->goal, &converter_problem)

	{

	}

	void Domain::add_new_current_state(const State& state)
	{
		states.push_back(state);
	}

	const State& Domain::get_current_state() const
	{
		return states.back();
	}

	const Agents* Domain::get_agents() const
	{
		return &agents;
	}

	const Agent* Domain::get_agent(size_t index) const
	{
		return agents.get(index);
	}

	const Agent* Domain::get_agent(Agent_Id id) const
	{
		return agents.get(id);
	}

	const Agent* Domain::get_agent(const std::string& name) const
	{
		return agents.get(name);
	}

	const Atoms* Domain::get_atoms(const std::string& type) const
	{
		return atom_lookup.get_atoms(type);
	}

	const Atom* Domain::get(const std::string& atom_name) const
	{
		return atom_lookup.get(atom_name);
	}

	const Propositions_Lookup& Domain::get_propositions_lookup() const
	{
		return propositions_lookup;
	}

	const Atom_Lookup& Domain::get_atom_lookup() const
	{
		return atom_lookup;
	}

	bool Domain::is_rigid(const Proposition_Instance* proposition) const
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

	bool Domain::perform_action(const Action* action)
	{
		PRINT_ACTION_TO_CONSOLE(*action);
		const State& current_state = get_current_state();
		std::optional<State> product_update = current_state.product_update(action, *this);
		if (!product_update.has_value())
		{
			return false;
		}

		product_update.value().contract();
		add_new_current_state(product_update.value());
		return true;
	}

	bool Domain::perform_action(const std::string& name, const std::vector<std::string>& arguments)
	{
		Atoms temp_arguments;
		temp_arguments.reserve(arguments.size());
		for (auto& argument : arguments)
		{
			temp_arguments.insert(get(argument));
		}

		auto action = Action(action_library.get_general_action(name), propositions_lookup, temp_arguments, agents);
		return perform_action(&action);
	}

}