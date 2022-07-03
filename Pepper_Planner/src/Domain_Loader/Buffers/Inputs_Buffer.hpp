#pragma once

#include <string>
#include <vector>

#include "Formula_Types.hpp"

namespace del
{
	class Input
	{
	public:
		Input() = delete;
		Input(const std::string& type, const std::string& name);
		const std::string& get_type() const;
		const std::string& get_name() const;
		std::string to_string() const;
	private:
		std::string type;
		std::string name;
	};

	class Inputs
	{
	public:
		Inputs();
		void add(const std::string& type, const std::string& name);
		size_t get_index(const Input& input) const;
		size_t get_index(const std::string& name) const;
		const Input& get(size_t index) const;
		size_t size() const;
		std::vector<Atom_Id> convert_to_atoms(const std::vector<std::string>& variables) const;
		std::vector<Input>::const_iterator begin() const;
		std::vector<Input>::const_iterator end() const;
	private:
		std::vector<Input> inputs;
	};

	class Inputs_Buffer
	{
	public:
		Inputs_Buffer();
		void add(const std::string& type, const std::string& name);
		Inputs get();
	private:
		Inputs inputs;
	};
}
