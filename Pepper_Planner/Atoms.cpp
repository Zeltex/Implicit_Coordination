#include "Atoms.hpp"

#include "Domain.hpp"

namespace del
{
	const Atom_Id& Atoms::at(size_t index) const
	{
		return atoms.at(index);
	}

	void Atoms::set(size_t index, const Atom_Id& atom)
	{
		atoms.at(index) = atom;
	}

	void Atoms::reserve(size_t size)
	{
		atoms.reserve(size);
	}

	void Atoms::insert(const Atom_Id& atom)
	{
		atoms.push_back(atom);
	}

	std::string Atoms::to_string(const Domain& domain) const
	{
		std::string result;
		for (const Atom_Id& atom_id : atoms)
		{
			result += domain.get_atom_name(atom_id) + " ";
		}
		return result;
	}
}