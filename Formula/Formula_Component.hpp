#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <map>

#include "Formula_Types.hpp"
#include "Formula_Input_Interface.hpp"
#include "Propositions.hpp"

namespace del {
	struct Formula_Component {
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas



		const char delim = ';';
		std::string to_string(const std::vector<Formula_Component>& all_formulas, const Domain& domain) const;
		bool valuate(const std::vector<Formula_Component>& all_formulas, const size_t world_id, const Formula_Input_Interface* input_interface) const;

		std::string get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas, const Domain& domain) const;
		Formula_Types get_type() const;
		const Proposition& get_proposition() const;

		Formula_Component() = default;

		Formula_Component(const Formula_Component& other, const std::map<Proposition, Proposition>& general_to_ground);

		// Top, Bot
		Formula_Component(Formula_Types type):
			type(type), prop(), formula(), formulas(std::vector<Formula_Id>()), agent(size_t{ 9999 }) {};

		// Prop
		Formula_Component(Formula_Types type, Proposition prop) :
			type(type), prop(prop), formula(), formulas(std::vector<Formula_Id>()), agent(size_t{ 9999 }) {};

		// And, Or
		Formula_Component(Formula_Types type, std::vector<Formula_Id> formulas) : 
			type(type), prop(), formula(), formulas(formulas), agent(size_t{ 99999 }) {};

		// Not, Everyone_Believes, Common_Knowledge
		Formula_Component(Formula_Types type, Formula_Id formula) : 
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(size_t{ 99999 }) {};

		// Believes
		Formula_Component(Formula_Types type, size_t agent, Formula_Id formula) : 
			type(type), prop(), formula(formula), formulas(std::vector<Formula_Id>()), agent(agent)  {};
		Formula_Types type;
		Proposition prop;
		Formula_Id formula;
		std::vector<Formula_Id> formulas;
		Proposition agent;
	private:

	};
}