#include "Atom_Buffer.hpp"

#include "Formula_Types.hpp"
#include "Inputs_Buffer.hpp"
#include "General_Objects.hpp"

#include <assert.h>

namespace del
{
	void Atom_Buffer::set(Inputs& inputs)
	{
		for (const Input& input : inputs)
		{
			atoms.insert({ input.get_name(), atoms.size() });
		}
	}

	void Atom_Buffer::set(General_Objects& objects)
	{
		atoms = objects.get_atom_name_to_id();
	}
	
	Atom_Id Atom_Buffer::get(const std::string& name)
	{
		if (name == REST_KEYWORD)
		{
			return { REST_INDEX };
		}
		else
		{
			assert(atoms.find(name) != atoms.end());
			return atoms.at(name);
		}
	}
}