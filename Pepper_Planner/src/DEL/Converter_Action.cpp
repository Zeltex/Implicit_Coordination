#include "Converter_Action.hpp"

#include "Agents.hpp"
#include "Atoms.hpp"
#include "Inputs_Buffer.hpp"
#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance.hpp"
#include "Propositions_Lookup.hpp"

#include <assert.h>

namespace del 
{

	Converter_Action::Converter_Action(const Propositions_Lookup& propositions_lookup, const Inputs& inputs, const Atoms& arguments, const Agents& agents)
		: propositions_lookup(&propositions_lookup), inputs(&inputs), arguments(&arguments), agents(&agents)
	{
		assert(inputs.size() == arguments.size());
		auto it1 = inputs.begin();
		auto it2 = arguments.begin();
		for (; it1 != inputs.end(); ++it1, ++it2)
		{
			general_atom_conversion.insert({it1->get_name(), *it2});
		}
	}

	void Converter_Action::set_rest(const Agent* agent)
	{
		if (rest_agent != nullptr)
		{
			general_atom_conversion.erase(general_atom_conversion.find(REST_KEYWORD));
		}

		if (agent != nullptr)
		{
			rest_agent = agent;
			general_atom_conversion.insert({ REST_KEYWORD, agent->get_atom() });
		}
	}

	const Proposition_Instance* Converter_Action::convert(const General_Proposition_Instance* general_instance) const
	{
		return propositions_lookup->get(Proposition_Instance{ general_instance, general_atom_conversion });
	}

	const Agent* Converter_Action::convert(const std::string& agent) const
	{
		if (agent == REST_KEYWORD)
		{
			assert(rest_agent != nullptr);
			return rest_agent;
		}

		assert(general_atom_conversion.find(agent) != general_atom_conversion.end());
		return agents->get(general_atom_conversion.at(agent));
	}
}