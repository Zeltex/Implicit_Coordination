#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>

#include "Types.hpp"
#include "../Formula/Formula_Component.hpp"

namespace del {

	class Formula {
	public:
		Formula():root(0) {}
		Formula(const Formula& other, const std::unordered_map<std::string, std::string>& input_to_atom);
		std::string to_string() const;
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


		Formula_Id root;
		std::vector<Formula_Component> formulas;
	private:
	};
	
}