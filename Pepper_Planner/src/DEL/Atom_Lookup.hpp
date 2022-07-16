#pragma once
#include <map>
#include <string>
#include <set>

#include "Atoms.hpp"
#include "Formula_Types.hpp"

namespace del {
	class General_Objects;
	class Atom_Lookup
	{
	public:
		Atom_Lookup(const General_Objects& general_objects);
		const Atoms* get_atoms(const std::string& type) const;
		const Atom* get(const std::string& atom_name) const;
	private:
		std::map<std::string, Atoms> type_to_atom;
		std::map<std::string, const Atom*> name_to_atom;
		std::vector<Atom> atoms;
	};
}