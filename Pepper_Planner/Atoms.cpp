#include "Atoms.hpp"

#include <assert.h>

namespace del
{
	Atom::Atom(size_t id, const std::string& name)
		: id(id), name(name)
	{

	}

	Atom::Atom(Atom_Id id, const std::string& name)
		: id(id), name(name)
	{

	}

	const std::string& Atom::get_name() const
	{
		return name;
	}
	
	Atom_Id Atom::get_id() const
	{
		return id;
	}

	const Atom& Atoms::at(size_t index) const
	{
		assert(index < atoms.size());
		return atoms.at(index);
	}

	void Atoms::set(size_t index, const Atom& atom)
	{
		assert(index < atoms.size());
		atoms.at(index) = atom;
	}

	void Atoms::reserve(size_t size)
	{
		atoms.reserve(size);
	}

	void Atoms::insert(const Atom& atom)
	{
		atoms.push_back(atom);
	}

	std::string Atoms::to_string(const Domain& domain) const
	{
		std::string result;
		for (const Atom& atom : atoms)
		{
			result += atom.get_name() + " ";
		}
		return result;
	}

	std::vector<Atom>::const_iterator Atoms::begin() const
	{
		return atoms.begin();
	}

	std::vector<Atom>::const_iterator Atoms::end() const
	{
		return atoms.end();
	}
}