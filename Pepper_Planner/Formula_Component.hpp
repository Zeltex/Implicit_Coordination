#pragma once

#include "Types.hpp"
#include <string>
#include <vector>
#include <unordered_set>

namespace del {
	struct Formula_Component {
		// TODO - Could probably be done more elegant
		friend class Formula_Creator;
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas
		Formula_Types type;
		std::string prop;
		Formula_Component* formula;
		std::vector<Formula_Component*> formulas;
		Agent_Id agent;


		const char delim = ';';
		std::string to_string();
		bool valuate(std::unordered_set<std::string>& propositions);

		~Formula_Component() {
			if (type == Formula_Types::Not ||
				type == Formula_Types::Everyone_Believes ||
				type == Formula_Types::Common_Knowledge ||
				type == Formula_Types::Believes) {
				delete formula;
			}
			if (type == Formula_Types::And ||
				type == Formula_Types::Or) {
				for (Formula_Component* formula : formulas) {
					delete formula;
				}
			}

		};

	private:
		Formula_Component() = delete;
		
		// Top, Bot
		Formula_Component(Formula_Types type):
			type(type), prop(""), formula(0), formulas(std::vector<Formula_Component*>()), agent(Agent_Id{ 9999 }) {};

		// Prop
		Formula_Component(Formula_Types type, std::string prop) : 
			type(type), prop(prop), formula(0), formulas(std::vector<Formula_Component*>()), agent(Agent_Id{ 9999 }) {};

		// And, Or
		Formula_Component(Formula_Types type, std::vector<Formula_Component*> formulas) : 
			type(type), prop(""), formula(0), formulas(formulas), agent(Agent_Id{ 99999 }) {};

		// Not, Everyone_Believes, Common_Knowledge
		Formula_Component(Formula_Types type, Formula_Component* formula) : 
			type(type), prop(""), formula(formula), formulas(std::vector<Formula_Component*>()), agent(Agent_Id{ 99999 }) {};

		// Believes
		Formula_Component(Formula_Types type, Agent_Id agent, Formula_Component* formula) : 
			type(type), prop(""), formula(formula), formulas(std::vector<Formula_Component*>()), agent(agent)  {};

		std::string get_string_component(const std::vector<Formula_Component*>& formulas) const;

	};
}