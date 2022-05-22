#pragma once
#include <map>
#include <Proposition_Instance.hpp>
#include <Propositions.hpp>

namespace del {
	class Atom_Lookup;
	class General_Typed_Propositions;
	class Propositions_Lookup
	{
	public:
		Propositions_Lookup(const General_Typed_Propositions& typed_propositions, const Atom_Lookup& atom_lookup);
		const Proposition& get(const Proposition_Instance& instance) const;
		const Proposition_Instance& get_instance(const Proposition& proposition) const;
	private:
		std::map<Proposition_Instance, Proposition> instance_to_proposition;
		std::map<Proposition, Proposition_Instance> proposition_to_instance;
	};
}