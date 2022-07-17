#include "Atom_Lookup.hpp"

#include "General_Objects.hpp"

#include <assert.h>

namespace del
{
	const Atoms* Atom_Lookup::get_atoms(const std::string& type) const
	{
		assert(type_to_atom.find(type) != type_to_atom.end());
		return &type_to_atom.at(type);
	}

	const Atom* Atom_Lookup::get(const std::string& atom_name) const
	{
		return name_to_atom.at(atom_name);
	}

	Atom_Lookup::Atom_Lookup(const General_Objects& general_objects)
	{
		atoms.reserve(general_objects.size());

		for (auto& [type, object_atoms] : general_objects.objects)
		{
			Atoms type_atoms;
			for (const std::string& atom_name : object_atoms)
			{
				atoms.emplace_back(atom_name, atoms.size());
				const Atom* atom = &atoms.back();
				type_atoms.insert(atom);
				name_to_atom.insert({ atom_name, atom });
			}
			type_to_atom.insert({ type, std::move(type_atoms) });
		}
	}
}