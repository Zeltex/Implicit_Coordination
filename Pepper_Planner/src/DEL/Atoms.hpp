#pragma once

#include "Formula_Types.hpp"

#include <vector>

namespace del
{
	class Atom
	{
	public:
		Atom(const std::string& name, size_t id);
		const std::string& get_name() const;
		const size_t& get_id() const;
	private:
		const std::string name;
		const size_t id;
	};

	class Atoms
	{
	public:
		const Atom* at(size_t index) const;
		void set(size_t index, const Atom* atom);
		void reserve(size_t size);
		void insert(const Atom* atom);
		std::string to_string() const;
		size_t size() const { return atoms.size(); }
		const Atom* operator[](size_t index) const { return atoms.at(index); }

		std::vector<const Atom*>::const_iterator begin() const;
		std::vector<const Atom*>::const_iterator end() const;

	private:
		std::vector<const Atom*> atoms;
	};
}