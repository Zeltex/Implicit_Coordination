#pragma once
#include <string>
#include <deque>

#include "Atom_Buffer.hpp"
#include "Formula_Types.hpp"
#include "General_Formula.hpp"
#include "General_Formula_Component.hpp"
#include "Propositions.hpp"

namespace del
{
	class General_Agents;
	class Proposition_Instance_Buffer;

	class Formula_Buffer
	{
	public:
		void push_pop_formula_top();
		void push_pop_formula_prop(Proposition_Instance_Buffer& proposition_instance_buffer);
		void push_formula(const std::string& type);
		void pop_formula_believes(const General_Agents& general_agents, const std::string& input);
		void pop_formula();
		General_Formula get();
	private:
		General_Formula formula;
		std::deque<General_Formula_Component*> formula_buffer;
		std::deque<Formula_Types> formula_buffer_type;
	};
}