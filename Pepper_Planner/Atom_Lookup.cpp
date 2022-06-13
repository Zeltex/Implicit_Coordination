#include "Atom_Lookup.hpp"

#include "General_Objects.hpp"

#include <assert.h>

namespace del
{
	const Atoms& Atom_Lookup::get_atoms(const std::string& type) const
	{
		assert(type_to_atom.find(type) != type_to_atom.end());
		return type_to_atom.at(type);
	}

	const Atom& Atom_Lookup::get_atom(const Atom_Id& atom_id) const
	{
		return id_to_atom.at(atom_id.id);
	}

	const Atom& Atom_Lookup::get_atom(const std::string& atom_name) const
	{
		return name_to_atom.at(atom_name);
	}

	Atom_Lookup::Atom_Lookup(const General_Objects& general_objects)
	{
		// TODO - This should generate all possible propositions
		for (auto& [type, atoms] : general_objects.objects)
		{
			type_to_atom.insert({ type, Atoms{} });
			Atoms& type_atoms = type_to_atom.at(type);
			for (const std::string& atom_name : atoms)
			{
				Atom_Id atom_id = general_objects.get_atom_id(atom_name);
				Atom atom { atom_id, atom_name };
				type_atoms.insert(atom);
				name_to_atom.insert({ atom_name, atom });
				id_to_atom.insert({ atom_id, atom });
			}
		}
	}
}