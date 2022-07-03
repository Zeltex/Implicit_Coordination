#pragma once

#include <string>
#include <list>
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
		Formula(const Formula& other) = delete;
		Formula(Formula&& other);
		Formula operator=(const Formula& other) = delete;

		Formula& operator=(Formula&& other) noexcept;

		Formula() {}
		Formula(const Formula& other, const Converter& general_to_ground);
		void reset();

		std::string to_string(const Domain& domain) const;
		bool valuate(const World_Id& world_id, const Domain& domain, const State& state) const;

		bool valuate_plausability(const Propositions& propositions) const;
		Formula_Component* f_top();
		Formula_Component* f_bot();
		Formula_Component* f_prop(Proposition proposition);
		Formula_Component* f_not(Formula_Component* formula);
		Formula_Component* f_believes(const Agent_Id& agent, Formula_Component* formula);
		Formula_Component* f_everyone_Believes(Formula_Component* formula);
		Formula_Component* f_common_Knowledge(Formula_Component* formula);
		Formula_Component* f_and(Formula_Component* input0, Formula_Component* input1);
		Formula_Component* f_or(Formula_Component* input0, Formula_Component* input1);


	private:
		std::list<Formula_Component> formulas;
	};
	
}