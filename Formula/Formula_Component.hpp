#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Formula_Types.hpp"
#include "Formula_Input_Interface.hpp"

namespace del {
	struct Formula_Component {
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas



		const char delim = ';';
		std::string to_string(const std::vector<Formula_Component>& all_formulas, const std::unordered_map<size_t, std::string>& id_to_atom) const;
		bool valuate(const std::vector<Formula_Component>& all_formulas, const size_t world_id, const Formula_Input_Interface* input_interface) const;

		std::string get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas, const std::unordered_map<size_t, std::string>& id_to_atom) const;
		Formula_Types get_type() const;
		const Proposition_Instance& get_proposition() const;

		Formula_Component() = default;

		Formula_Component(const Formula_Component& other, const std::unordered_map<size_t, Atom_Id>& input_to_atom, const std::unordered_map<size_t, size_t>& input_to_agent);

		// Top, Bot
		Formula_Component(Formula_Types type):
			type(type), prop(), formula(), formulas(std::vector<Formula_Id>()), agent(size_t{ 9999 }) {};

		// Prop
		Formula_Component(Formula_Types type, Proposition_Instance prop) :
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
		Proposition_Instance prop;
		Formula_Id formula;
		std::vector<Formula_Id> formulas;
		size_t agent;
	private:

	};
}