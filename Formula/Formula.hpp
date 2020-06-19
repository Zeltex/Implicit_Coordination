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
		Formula_Id root;
		std::vector<Formula_Component> formulas;
		std::string to_string() const;
		bool valuate(const std::unordered_set<std::string> propositions) const;
		Formula_Id f_top();
		Formula_Id f_bot();
		Formula_Id f_prop(std::string prop);
		Formula_Id f_not(Formula_Id formula);
		Formula_Id f_and(std::vector<Formula_Id> formulas);
		Formula_Id f_or(std::vector<Formula_Id> formulas);
		Formula_Id f_believes(size_t agent, Formula_Id formula);
		Formula_Id f_everyone_Believes(Formula_Id formula);
		Formula_Id f_common_Knowledge(Formula_Id formula);
	private:
	};
	
}