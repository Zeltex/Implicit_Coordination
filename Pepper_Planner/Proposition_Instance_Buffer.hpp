#pragma once
#include <string>
#include <vector>
#include "Proposition_Instance.hpp"
#include "Propositions.hpp"

namespace del
{
	class Atom_Lookup;
	class General_Objects;
	class Inputs;
	class Propositions_Lookup;
	class Variables_Buffer;

	class Proposition_Instance_Buffer
	{
	friend class Propositions;
	public:
		void set(Proposition_Instance_Buffer& other);
		void set_and_consume(Proposition_Instance_Buffer& other);
		void add(const std::string& name, Variables_Buffer& variables_buffer, const Inputs& inputs);
		void add(const std::string& name, Variables_Buffer& variables_buffer, const General_Objects& general_objects);
		Proposition_Instance_Buffer move();
		std::vector<Proposition_Instance> get();
		Proposition to_proposition(const Proposition_Instance& proposition_instance) const;
		std::map<Proposition, Proposition> create_converter(const Propositions_Lookup& propositions_lookup) const;
		std::map<Proposition_Instance, Proposition>::const_iterator begin() const;
		std::map<Proposition_Instance, Proposition>::const_iterator end() const;
	private:

		std::map<Proposition_Instance, Proposition> instance_to_proposition;
		std::vector<Proposition_Instance> proposition_instances;
		Propositions propositions;
	};
}