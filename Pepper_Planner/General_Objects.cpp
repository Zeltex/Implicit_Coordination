#include "General_Objects.hpp"
#include "Variables_Buffer.hpp"
#include "General_Agents.hpp"

namespace del 
{

	void General_Objects::add(const std::string& type, Variables_Buffer& variables_buffer, General_Agents& agents)
	{
		objects.insert({ type, variables_buffer.get() });
		for (const std::string& atom : objects.at(type))
		{
			atom_name_to_id.insert({ atom, Atom_Id{atom_name_to_id.size()} });
		}

		// A little hardcoded, but works
		if (type == "agent")
		{
			agents.set(objects.at(type), *this);
		}
	}

	Atom_Id General_Objects::get_atom_id(const std::string& name) const
	{
		return atom_name_to_id.at(name);
	}

	const std::map<std::string, Atom_Id>& General_Objects::get_atom_name_to_id() const
	{
		return atom_name_to_id;
	}
}