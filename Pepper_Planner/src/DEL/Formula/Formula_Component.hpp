#pragma once

#include <string>
#include <vector>

#include "Formula_Types.hpp"
#include "Propositions.hpp"
#include "Types.hpp"

namespace del {
	class Agent;
	class Domain;
	class Formula;
	struct General_Formula_Component;
	struct World_Id;

	struct Formula_Component {
		const char delim = ';';
		std::string to_string() const;
		bool valuate(const World_Id& world_id, const Domain& domain, const State& state) const;
		bool valuate_plausability(const Propositions& propositions) const;

		Formula_Component() = default;

		Formula_Component& operator=(const Formula_Component& other);

		Formula_Component(Formula& formula, const General_Formula_Component* other, const Converter_Base* converter);

		// Prop
		Formula_Component(Formula_Types type, const Proposition_Instance* prop);

		// Believes
		Formula_Component(Formula_Types type, const Agent* agent, Formula_Component* formula);

		// And/Or
		Formula_Component(Formula_Types type, Formula_Component* input0=nullptr, Formula_Component* input1=nullptr);

		Formula_Types type;
		const void* data0;
		const void* data1;
	};
}