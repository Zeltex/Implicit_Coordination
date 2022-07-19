#pragma once

#include "Converter_Base.hpp"
#include "Propositions.hpp"
#include "Types.hpp"

#include <map>

namespace del
{
	class Agent;
	class Agents;
	class Atom;
	class Atoms;
	class General_Proposition_Instance;
	class Inputs;
	struct proposition_instance;
	class Propositions_Lookup;

	class Converter_Problem : public Converter_Base
	{
	public:
		Converter_Problem(const Propositions_Lookup* propositions_lookup, const Atom_Lookup* atom_lookup, const Agents* agents);

		const Proposition_Instance* convert(const General_Proposition_Instance* general_instance) const override;
		const Agent* convert(const std::string& agent) const override;

	private:
		std::map<std::string, const Atom*> general_atom_conversion;

		const Propositions_Lookup* propositions_lookup;
		const Atom_Lookup* atom_lookup;
		const Agents* agents;
	};
}