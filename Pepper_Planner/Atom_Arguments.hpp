#pragma once

#include <Formula_Types.hpp>

#include <map>


namespace del
{
	class Atoms;

	class Atom_Arguments
	{
	public:
		Atom_Arguments(const Atoms& atoms);
		Atom_Id get(Atom_Id index) const;
		void set(size_t index, Atom_Id value);
	private:
		std::map<size_t, Atom_Id> atoms;
	};
}