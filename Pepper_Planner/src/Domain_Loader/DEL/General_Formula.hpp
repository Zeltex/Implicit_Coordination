#pragma once

#include "General_Formula_Component.hpp"

namespace del
{
	class General_Formula
	{
		friend class Formula;
	public:
		General_Formula(const General_Formula& other) = delete;
		General_Formula(General_Formula&& other) noexcept;
		General_Formula operator=(const General_Formula& other) = delete;
		General_Formula& operator=(General_Formula&& other) noexcept;

		General_Formula() {}

		General_Formula_Component* f_top();
		General_Formula_Component* f_bot();
		General_Formula_Component* f_prop(General_Proposition_Instance proposition);
		General_Formula_Component* f_not(General_Formula_Component* General_Formula);
		General_Formula_Component* f_believes(const std::string& agent, General_Formula_Component* General_Formula);
		General_Formula_Component* f_everyone_Believes(General_Formula_Component* General_Formula);
		General_Formula_Component* f_common_Knowledge(General_Formula_Component* General_Formula);
		General_Formula_Component* f_and(General_Formula_Component* input0, General_Formula_Component* input1);
		General_Formula_Component* f_or(General_Formula_Component* input0, General_Formula_Component* input1);

		void reset();

	private:
		// root is always formulas.back()
		std::list<General_Formula_Component> formulas;
	};
}