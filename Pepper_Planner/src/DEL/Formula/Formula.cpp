#include "Formula.hpp"

#include "Atom_Lookup.hpp"
#include "Converter_Base.hpp"
#include "General_Formula.hpp"
#include "Propositions_Lookup.hpp"

#include <assert.h>

namespace del
{

	Formula::Formula(const General_Formula& other, const Converter_Base* converter)
	{
		formulas.resize(other.formulas.size());
		if (other.formulas.empty())
		{
			return;
		}

		root = &formulas.emplace_back(*this, &other.formulas.back(), converter);
	}


	Formula& Formula::operator=(Formula&& other)
	{
		formulas = std::move(other.formulas);
		root = other.root;
		other.formulas = {};
		other.root = nullptr;
		return *this;
	}

	Formula::Formula(Formula&& other)
	{
		formulas = std::move(other.formulas);
		root = other.root;
		other.formulas = {};
		other.root = nullptr;
	}

	void Formula::reset()
	{
		formulas = {};
	}

	std::string Formula::to_string() const
	{
		if (formulas.empty())
		{
			return Formula_Converter::type_to_string(Formula_Types::Top);
		}
		else
		{
			return root->to_string();
		}
	}

	bool Formula::valuate_plausability(const Propositions& propositions) const
	{
		if (formulas.empty())
		{
			return true;
		}
		else
		{
			return root->valuate_plausability(propositions);
		}
	}

	bool Formula::valuate(const World_Id& world_id, const Domain& domain, const State& state) const
	{
		if (formulas.empty())
		{
			return true;
		}
		else
		{
			return root->valuate(world_id, domain, state);
		}
	}

	Formula_Component* Formula::f_top()
	{
		formulas.emplace_back(Formula_Types::Top);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_bot()
	{
		formulas.emplace_back(Formula_Types::Bot);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_prop(const Proposition_Instance* proposition)
	{
		formulas.emplace_back(Formula_Types::Prop, proposition);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_not(Formula_Component* formula)
	{
		formulas.emplace_back(Formula_Types::Not, formula);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_and(Formula_Component* input0, Formula_Component* input1)
	{
		formulas.emplace_back(Formula_Types::And, input0, input1);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_or(Formula_Component* input0, Formula_Component* input1)
	{
		formulas.emplace_back(Formula_Types::Or, input0, input1);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_believes(const Agent* agent, Formula_Component* formula)
	{
		formulas.emplace_back(Formula_Types::Believes, agent, formula);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_everyone_Believes(Formula_Component* formula)
	{
		formulas.emplace_back(Formula_Types::Everyone_Believes, formula);
		root = &formulas.back();
		return root;
	}

	Formula_Component* Formula::f_common_Knowledge(Formula_Component* formula)
	{
		formulas.emplace_back(Formula_Types::Common_Knowledge, formula);
		root = &formulas.back();
		return root;
	}
}