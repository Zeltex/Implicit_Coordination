#pragma once

#include <string>
#include <vector>

#include "Formula_Types.hpp"
#include "Formula_Input_Interface.hpp"
#include "Propositions.hpp"
#include "Types.hpp"

namespace del {
	class Converter;
	class Domain;
	class State;
	struct World_Id;

	struct Formula_Component {
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas

		const char delim = ';';
		std::string to_string(const std::vector<Formula_Component>& all_formulas, const Domain& domain) const;
		bool valuate(const std::vector<Formula_Component>& all_formulas, const World_Id& world_id, const Domain& domain, const State& state) const;
		bool valuate_plausability(const std::vector<Formula_Component>& all_formulas, const Propositions& propositions) const;
		std::string get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas, const Domain& domain) const;
		Formula_Types get_type() const;
		const Proposition& get_proposition() const;

		Formula_Component() = default;

		Formula_Component(const Formula_Component& other, const Converter& general_to_ground);

		// Top, Bot
		Formula_Component(Formula_Types type):
			type(type), prop(), formula(), formulas(std::vector<Formula_Id>()), agent(EMPTY_INDEX) {};

		// Prop
		Formula_Component(Formula_Types type, Proposition prop) :
			type(type), prop(prop), formula(), formulas(std::vector<Formula_Id>()), agent(EMPTY_INDEX) {};

		// And, Or
		Formula_Component(Formula_Types type, std::vector<Formula_Id> formulas) : 
			type(type), prop(), formula(), formulas(formulas), agent(EMPTY_INDEX) {};

		// Not, Everyone_Believes, Common_Knowledge
		Formula_Component(Formula_Types type, Formula_Id formula) : 
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(EMPTY_INDEX) {};

		// Believes
		Formula_Component(Formula_Types type, Agent_Id agent, Formula_Id formula) :
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(agent)  {};
		Formula_Types type;
		Proposition prop;
		Formula_Id formula;
		std::vector<Formula_Id> formulas;
		Agent_Id agent;
	private:

	};
}