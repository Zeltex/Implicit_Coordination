#pragma once
#include <string>
#include <vector>
#include "Proposition_Instance.hpp"
#include "Variables_Buffer.hpp"
#include "Propositions.hpp"

namespace del
{
	class Inputs;
	class Atom_Lookup;
	class Propositions_Lookup;
	class Proposition_Instance_Buffer
	{
	friend class Propositions;
	public:
		void set(Proposition_Instance_Buffer& other);
		void add(const std::string& name, Variables_Buffer& variables_buffer, const Inputs& inputs);
		//void push_proposition_instance(const std::string name, Variables_Buffer& variables_buffer, const Inputs& inputs);
		//Propositions get();
		std::vector<Proposition_Instance> get();
		Proposition to_proposition(const Proposition_Instance& proposition_instance) const;
		std::map<Proposition, Proposition> create_converter(const Propositions_Lookup& propositions_lookup) const;
	private:

		std::map<Proposition_Instance, Proposition> instance_to_proposition;
		std::vector<Proposition_Instance> proposition_instances;
		Propositions propositions;
	};
}