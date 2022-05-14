#pragma once
#include <string>
#include <vector>
#include <Formula_Types.hpp>
#include <Formula.hpp>
#include <General_Atoms.hpp>
#include "Atom_Buffer.hpp"

namespace del
{
	class Formula_Buffer
	{
	public:
		void push_pop_formula(const std::string& type);
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
		//General_Atoms atoms;
		Atom_Buffer atoms;
	};
}