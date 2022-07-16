#pragma once
#include <map>
#include <Proposition_Instance.hpp>
#include <Propositions.hpp>

namespace del {
	class Atom_Lookup;
	class General_State;
	class General_Typed_Propositions;
	class Proposition_Instance_Buffer;

	class Propositions_Lookup
	{
	public:
		Propositions_Lookup(const General_Typed_Propositions& typed_propositions, const Atom_Lookup& atom_lookup, const General_State& state, const Proposition_Instance_Buffer& proposition_instance_buffer);
		const Proposition_Instance* get(const Proposition_Instance& instance) const;
		const Proposition_Instance* get(const General_Proposition_Instance& instance, const Atom_Lookup& atom_lookup) const;
		//const Proposition_Instance* get(const Proposition_Instance& instance, const Atoms& arguments) const;
	private:
		std::set<Proposition_Instance> propositions;
	};
}
