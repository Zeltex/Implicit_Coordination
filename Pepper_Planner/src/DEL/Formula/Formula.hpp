#pragma once

#include <string>
#include <list>

#include "Formula_Types.hpp"
#include "Formula_Component.hpp"
#include "Formula_Converter.hpp"

namespace del {
	struct Agent_Id;
	class Atom_Lookup;
	class Converter_Base;
	class General_Formula;
	class Propositions_Lookup;

	class Formula {
		friend struct Formula_Component;
	public:
		Formula(const Formula& other) = delete;
		Formula(Formula&& other);
		Formula operator=(const Formula& other) = delete;

		Formula& operator=(Formula&& other);

		Formula() {}
		Formula(const General_Formula& other, const Converter_Base* converter);
		void reset();

		std::string to_string() const;
		bool valuate(const World_Id& world_id, const Domain& domain, const State& state) const;

		bool valuate_plausability(const Propositions& propositions) const;
		Formula_Component* f_top();
		Formula_Component* f_bot();
		Formula_Component* f_prop(const Proposition_Instance* proposition);
		Formula_Component* f_not(Formula_Component* formula);
		Formula_Component* f_believes(const Agent* agent, Formula_Component* formula);
		Formula_Component* f_everyone_Believes(Formula_Component* formula);
		Formula_Component* f_common_Knowledge(Formula_Component* formula);
		Formula_Component* f_and(Formula_Component* input0, Formula_Component* input1);
		Formula_Component* f_or(Formula_Component* input0, Formula_Component* input1);


	private:
		std::list<Formula_Component> formulas;
		Formula_Component* root;
	};
	
}