#pragma once

#include "Types.hpp"
#include <string>
#include <vector>
#include <unordered_set>

namespace del {
	struct Formula_Component {
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas



		const char delim = ';';
		std::string to_string(const std::vector<Formula_Component>& all_formulas) const;
		bool valuate(const  std::unordered_set<std::string>& propositions, const std::vector<Formula_Component>& all_formulas) const;

		std::string get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas) const;

		Formula_Component() = delete;

		// Top, Bot
		Formula_Component(Formula_Types type):
			type(type), prop(), formula(), formulas(std::vector<Formula_Id>()), agent(Agent_Id{ 9999 }) {};

		// Prop
		Formula_Component(Formula_Types type, std::string prop) : 
			type(type), prop(prop), formula(), formulas(std::vector<Formula_Id>()), agent(Agent_Id{ 9999 }) {};

		// And, Or
		Formula_Component(Formula_Types type, std::vector<Formula_Id> formulas) : 
			type(type), prop(), formula(), formulas(formulas), agent(Agent_Id{ 99999 }) {};

		// Not, Everyone_Believes, Common_Knowledge
		Formula_Component(Formula_Types type, Formula_Id formula) : 
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(Agent_Id{ 99999 }) {};

		// Believes
		Formula_Component(Formula_Types type, Agent_Id agent, Formula_Id formula) : 
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(agent)  {};

	private:
		Formula_Types type;
		std::string prop;
		Formula_Id formula;
		std::vector<Formula_Id> formulas;
		Agent_Id agent;
	};
}