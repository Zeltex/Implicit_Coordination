#include "General_Atoms.hpp"

#include "Variables_Buffer.hpp"

#include <assert.h>
#include <stdexcept>

namespace del
{
	General_Atom::General_Atom(size_t id, const std::string& name)
		: id(id), name(name)
	{

	}

	General_Atom::General_Atom(Atom_Id id, const std::string& name)
		: id(id), name(name)
	{

	}
	
	const std::string& General_Atom::get_name() const
	{
		return name;
	}
	
	Atom_Id General_Atom::get_id() const
	{
		return id;
	}

	void General_Atoms::add(const std::string& type, const Variables_Buffer& variables)
	{

		// TODO - This should take the type into account aswell
		for (const std::string& entry : variables)
		{
			assert(!contains(entry));
			add(entry);
		}
	}

	const General_Atom& General_Atoms::get_or_add(const std::string& name)
	{
		if (!contains(name))
		{
			add(name);
		}
		return get(name);
	}

	void  General_Atoms::add_if_not_exists(const std::string& name, Atom_Id id)
	{
		if (!contains(name))
		{
			add(name, id);
		}
	}

	const General_Atom& General_Atoms::get(const std::string& name)
	{
		return name_to_atom.at(name);
	}

	bool General_Atoms::contains(const std::string& name) const
	{
		return name_to_atom.find(name) != name_to_atom.end();
	}

	void General_Atoms::add(const std::string& name)
	{
		add(name, { name_to_atom.size() });
	}

	void General_Atoms::add(const std::string& name, Atom_Id id)
	{
		name_to_atom.insert({ name, General_Atom(id, name) });
	}
}