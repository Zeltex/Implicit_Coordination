#include "Inputs_Buffer.hpp"

#include <assert.h>

namespace del
{
	Input::Input(const std::string& type, const std::string& name)
		: type(type), name(name)
	{

	}

	const std::string& Input::get_type() const
	{
		return type;
	}

	const std::string& Input::get_name() const
	{
		return name;
	}

	std::string Input::to_string() const
	{
		return type + " " + name;
	}

	Inputs::Inputs()
		: inputs()
	{

	}

	size_t Inputs::get_index(const Input& other) const
	{
		size_t counter = 0;
		for (const Input& input : inputs) {
			if (input.get_type() == other.get_type() && input.get_name() == other.get_name()) {
				return counter;
			}
			++counter;
		}
		assert(false);
		throw "Input '" + other.to_string() + "' not found";
	}

	void Inputs::add(const std::string& type, const std::string& name)
	{
		inputs.push_back({ type, name });
	}

	size_t Inputs::get_index(const std::string& name) const
	{
		size_t counter = 0;
		for (const Input& input : inputs) {
			if (input.get_name() == name) {
				return counter;
			}
			++counter;
		}

		if (name == REST_KEYWORD)
		{
			return REST_INDEX;
		}

		assert(false);
		throw "Input '" + name + "' not found";
	}

	const Input& Inputs::get(size_t index) const
	{
		return inputs.at(index);
	}

	size_t Inputs::size() const
	{
		return inputs.size();
	}

	std::vector<Atom_Id> Inputs::convert_to_atoms(const std::vector<std::string>& variables) const
	{
		std::vector<Atom_Id> atoms;
		for (const std::string& entry : variables)
		{
			Atom_Id id = (entry == REST_KEYWORD)
				? Atom_Id{ REST_INDEX }
				: Atom_Id{ get_index(entry) };
			atoms.push_back(id);
		}
		return atoms;
	}

	std::vector<Input>::const_iterator Inputs::begin() const
	{
		return inputs.begin();
	}

	std::vector<Input>::const_iterator Inputs::end() const
	{
		return inputs.end();
	}

	Inputs_Buffer::Inputs_Buffer()
		: inputs()
	{

	}

	void Inputs_Buffer::add(const std::string& type, const std::string& name)
	{
		inputs.add(type, name);
	}

	Inputs Inputs_Buffer::get()
	{
		Inputs temp = std::move(inputs);
		inputs = {};
		return temp;
	}
}