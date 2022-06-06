#pragma once
#include <string>
#include <vector>

#include "Atom_Buffer.hpp"
#include "Formula_Types.hpp"
#include "Formula.hpp"
#include "Propositions.hpp"

namespace del
{
	struct Proposition_Instance_Buffer;
	class Formula_Buffer
	{
	public:
		void push_pop_formula_top();
		void push_pop_formula_prop(Proposition_Instance_Buffer& proposition_instance_buffer);
		void push_formula(const std::string& type);
		std::tuple<Formula_Types, std::vector<Formula_Id>> pop_formula_info();
		void pop_formula(const std::string& input);
		void pop_formula();
		Formula get();
	private:
		Formula formula;
		std::vector<std::vector<Formula_Id>> formula_buffer;
		std::vector<Formula_Types> formula_buffer_type;
		std::vector<Proposition> propositions;
		Atom_Buffer atoms;
	};
}