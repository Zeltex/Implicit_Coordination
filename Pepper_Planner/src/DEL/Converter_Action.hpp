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

	class Converter_Action : public Converter_Base
	{
	public:
		Converter_Action(const Propositions_Lookup& propositions_lookup, const Inputs& inputs, const Atoms& arguments, const Agents& agents);
		void set_rest(const Agent* agent);

		const Proposition_Instance* convert(const General_Proposition_Instance* general_instance) const override;
		const Agent* convert(const std::string& agent) const override;

	private:
		std::map<std::string, const Atom*> general_atom_conversion;

		const Agent* rest_agent;

		const Propositions_Lookup* propositions_lookup;
		const Inputs* inputs;
		const Atoms* arguments;
		const Agents* agents;
	};
}