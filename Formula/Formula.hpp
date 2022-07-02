#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <memory>
#include <map>

#include "Formula_Types.hpp"
#include "Formula_Component.hpp"
#include "Formula_Converter.hpp"

namespace del {
	struct Agent_Id;
	class Converter;

	class Formula {
	public:
		Formula():root(0) {}
		Formula(const Formula& other, const Converter& general_to_ground);
		std::string to_string(const Domain& domain) const;
		bool valuate(const World_Id& world_id, const Domain& domain, const State& state) const;

		bool valuate_plausability(const Propositions& propositions) const;
		Formula_Id f_top();
		Formula_Id f_bot();
		Formula_Id f_prop(Proposition proposition);
		Formula_Id f_not(Formula_Id formula);
		Formula_Id f_and(std::vector<Formula_Id> formulas);
		Formula_Id f_or(std::vector<Formula_Id> formulas);
		Formula_Id f_believes(const Agent_Id& agent, Formula_Id formula);
		Formula_Id f_believes(std::string agent, Formula_Id formula, const std::unordered_map<std::string, Agent_Id>& context);
		Formula_Id f_everyone_Believes(Formula_Id formula);
		Formula_Id f_common_Knowledge(Formula_Id formula);

		const Formula_Component& get_component(Formula_Id formula) const;
		const Formula_Id& get_root() const;

	private:
		Formula_Id root;
		std::vector<Formula_Component> formulas;
	};
	
}