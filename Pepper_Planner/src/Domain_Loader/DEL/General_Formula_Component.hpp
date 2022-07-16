#pragma once

#include "Formula_Types.hpp"
#include "General_Proposition_Instance.hpp"
#include "Types.hpp"

namespace del
{

	class Converter;
	class Formula;
	class State;
	struct World_Id;

	struct General_Formula_Component
	{

		General_Formula_Component() = default;

		// Prop
		General_Formula_Component(Formula_Types type, General_Proposition_Instance prop);

		// Believes
		General_Formula_Component(Formula_Types type, std::string agent, General_Formula_Component* formula);

		// And/Or/not/top/bot
		General_Formula_Component(Formula_Types type, General_Formula_Component* input0 = nullptr, General_Formula_Component* input1 = nullptr);

		Formula_Types type;
		General_Formula_Component* data0;
		General_Formula_Component* data1;

		General_Proposition_Instance prop;
		std::string agent;
	};
}