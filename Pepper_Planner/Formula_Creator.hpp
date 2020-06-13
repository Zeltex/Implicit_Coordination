#pragma once

#include "Formula_Component.hpp"
#include "Types.hpp"

namespace del {
	class Formula_Creator {
	public:
		Formula_Component* f_top();
		Formula_Component* f_bot();
		Formula_Component* f_prop(std::string prop);
		Formula_Component* f_not(Formula_Component* formula);
		Formula_Component* f_and(std::vector<Formula_Component*> formulas);
		Formula_Component* f_or(std::vector<Formula_Component*> formulas);
		Formula_Component* f_believes(Agent_Id agent, Formula_Component* formula);
		Formula_Component* f_everyone_Believes(Formula_Component* formula);
		Formula_Component* f_common_Knowledge(Formula_Component* formula);
	private:
	};
}