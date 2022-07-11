#pragma once

#include <string>
#include <vector>

#include "Formula_Types.hpp"

#include "Propositions.hpp"
#include "Types.hpp"

namespace del {
	class Converter;
	class Domain;
	class Formula;
	class State;
	struct World_Id;

	struct Formula_Component {
		// TODO - Use (maybe) union to only hold one of prop, formula, formulas

		const char delim = ';';
		std::string to_string(const Domain& domain) const;
		bool valuate(const World_Id& world_id, const Domain& domain, const State& state) const;
		bool valuate_plausability(const Propositions& propositions) const;

		Formula_Component() = default;

		Formula_Component& operator=(const Formula_Component& other);
		Formula_Component(const Formula_Component& other, const Converter& general_to_ground);

		// Prop
		Formula_Component(Formula_Types type, Proposition prop) :
			type(type), data0(nullptr), data1(nullptr), prop(prop), agent(EMPTY_INDEX) {};

		// Believes
		Formula_Component(Formula_Types type, Agent_Id agent, Formula_Component* formula) :
			type(type), data0(nullptr), data1(formula), prop(), agent(agent)  {};


		// And/Or
		Formula_Component(Formula_Types type, Formula_Component* input0=nullptr, Formula_Component* input1=nullptr);

		Formula_Component* copy(Formula* formula, const Converter& general_to_ground) const;

		Formula_Types type;
		void* data0;
		void* data1;

		Proposition prop;
		Agent_Id agent;
	};
}