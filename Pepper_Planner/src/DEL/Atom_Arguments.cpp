#include "Atom_Arguments.hpp"

#include "Atoms.hpp"

namespace del
{

	Atom_Arguments::Atom_Arguments(const Atoms& atoms)
	{
		size_t counter = 0;
		for (const auto& entry : atoms)
		{
			this->atoms.insert({ counter++, entry.get_id() });
		}
	}

	bool Atom_Arguments::has(Atom_Id index) const
	{
		return atoms.find(index.id) != atoms.end();
	}

	Atom_Id Atom_Arguments::get(Atom_Id index) const
	{
		return (*(atoms.find(index.id))).second;
	}

	void Atom_Arguments::set(size_t index, Atom_Id value)
	{
		auto it = atoms.find(index);
		if (it == atoms.end())
		{
			atoms.insert({ index, value });
		}
		else
		{
			it->second = value;
		}
	}
}