#pragma once

#include "Formula_Types.hpp"

#include <vector>

namespace del
{
	class Domain;
	class Atoms
	{
	public:
		const Atom_Id& at(size_t index) const;
		void set(size_t index, const Atom_Id& atom);
		void reserve(size_t size);
		void insert(const Atom_Id& atom);
		std::string to_string(const Domain& domain) const;
		size_t size() const { return atoms.size(); }
		const Atom_Id& operator[](size_t index) const { return atoms.at(index); }
	private:
		std::vector<Atom_Id> atoms;
	};
}