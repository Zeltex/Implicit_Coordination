#pragma once

#include "Formula_Types.hpp"

#include <string>
#include <unordered_map>

namespace del {
	class Variables_Buffer;
	struct General_Atom 
	{
	public:
		General_Atom(size_t id, const std::string& name);
		General_Atom(Atom_Id id, const std::string& name);
		const std::string& get_name() const;
		Atom_Id get_id() const;
	private:
		Atom_Id id;
		std::string name;
	};

	struct General_Atoms 
	{
	public:
		void add(const std::string& type, const Variables_Buffer& variables);
		const General_Atom& get_or_add(const std::string& name);
		const General_Atom& get(const std::string& name);
		void add_if_not_exists(const std::string& name, Atom_Id id);
	private:
		bool contains(const std::string& name) const;
		void add(const std::string& name);
		void add(const std::string& name, Atom_Id id);
		std::unordered_map<std::string, General_Atom> name_to_atom;
	};
}