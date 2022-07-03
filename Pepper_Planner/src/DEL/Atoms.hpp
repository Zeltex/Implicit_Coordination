#pragma once

#include "Formula_Types.hpp"

#include <vector>

namespace del
{
	// An atom is simply a name, and referenced by id
	class Atom
	{
	public:
		Atom(size_t id, const std::string& name);
		Atom(Atom_Id id, const std::string& name);
		const std::string& get_name() const;
		Atom_Id get_id() const;
	private:
		Atom_Id id;
		std::string name;
	};

	class Domain;
	class Atoms
	{
	public:
		const Atom& at(size_t index) const;
		void set(size_t index, const Atom& atom);
		void reserve(size_t size);
		void insert(const Atom& atom);
		std::string to_string(const Domain& domain) const;
		size_t size() const { return atoms.size(); }
		const Atom& operator[](size_t index) const { return atoms.at(index); }

		std::vector<Atom>::const_iterator begin() const;
		std::vector<Atom>::const_iterator end() const;

	private:
		std::vector<Atom> atoms;
	};
}