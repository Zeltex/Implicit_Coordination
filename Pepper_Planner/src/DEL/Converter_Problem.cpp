#include "Converter_Problem.hpp"

#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Inputs_Buffer.hpp"
#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance.hpp"
#include "Propositions_Lookup.hpp"

#include <assert.h>

namespace del
{

	Converter_Problem::Converter_Problem(const Propositions_Lookup* propositions_lookup, const Atom_Lookup* atom_lookup, const Agents* agents)
		: propositions_lookup(propositions_lookup), atom_lookup(atom_lookup), agents(agents)
	{

	}

	const Proposition_Instance* Converter_Problem::convert(const General_Proposition_Instance* general_instance) const
	{
		return propositions_lookup->get(Proposition_Instance{ *general_instance, *atom_lookup });
	}

	const Agent* Converter_Problem::convert(const std::string& agent) const
	{
		return agents->get(agent);
	}
}