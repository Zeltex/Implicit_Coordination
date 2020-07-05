#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

#include "Formula_Types.hpp"
#include "Formula_Component.hpp"
#include "Formula_Converter.hpp"

namespace del {

	class Formula {
	public:
		Formula():root(0) {}
		Formula(const Formula& other, const std::unordered_map<size_t, Atom_Id>& input_to_atom);
		std::string to_string(const std::unordered_map<size_t, std::string>& id_to_atom) const;
		bool valuate(const std::vector<Proposition_Instance> propositions) const;
		Formula_Id f_top();
		Formula_Id f_bot();
		Formula_Id f_prop(Proposition_Instance proposition);
		Formula_Id f_not(Formula_Id formula);
		Formula_Id f_and(std::vector<Formula_Id> formulas);
		Formula_Id f_or(std::vector<Formula_Id> formulas);
		Formula_Id f_believes(size_t agent, Formula_Id formula);
		Formula_Id f_everyone_Believes(Formula_Id formula);
		Formula_Id f_common_Knowledge(Formula_Id formula);

		const Formula_Component& get_component(Formula_Id formula) const;
		const Formula_Id& get_root() const;

	private:
		Formula_Id root;
		std::vector<Formula_Component> formulas;
	};
	
}