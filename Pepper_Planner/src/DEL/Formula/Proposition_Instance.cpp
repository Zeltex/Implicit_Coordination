#include "Proposition_Instance.hpp"

#include <assert.h>

#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Domain.hpp"
#include "General_Proposition_Instance.hpp"


namespace del
{
	Proposition_Instance::Proposition_Instance() : name(), arguments()
	{
		for (auto& entry : arguments)
		{
			entry = nullptr;
		}
	}

	Proposition_Instance::Proposition_Instance(const General_Proposition_Instance& general_instance, const Atom_Lookup& atom_lookup)
		: name(general_instance.get_name())
	{
		size_t counter = 0;
		for (auto& arg : general_instance.arguments)
		{
			if (arg.empty())
			{
				arguments.at(counter) = nullptr;
			}
			else
			{
				arguments.at(counter) = atom_lookup.get(arg);
			}
			++counter;
		}
		flood_null(counter);
	}

	Proposition_Instance::Proposition_Instance(const General_Proposition_Instance* general_instance, const std::map<std::string, const Atom*>& converter)
		: name(general_instance->get_name()), arguments()
	{
		size_t counter = 0;
		for (auto& arg : general_instance->arguments)
		{
			assert(counter < arguments.size());
			if (arg.empty())
			{
				arguments.at(counter) = nullptr;
			}
			else
			{
				arguments.at(counter) = converter.at(arg);
			}
			++counter;
		}
		flood_null(counter);
	}

	Proposition_Instance::Proposition_Instance(const std::string& name, const Atoms& input, size_t id)
		: name(name), arguments(), id(id)
	{
		size_t counter = 0;
		for (const Atom* atom : input)
		{
			arguments[counter] = atom;
			++counter;
		}
		flood_null(counter);
	}

	Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0)
		: Proposition_Instance(name, atom_lookup.get(arg_0), nullptr, nullptr, nullptr, nullptr)
	{

	}

	Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1)
		: Proposition_Instance(name, atom_lookup.get(arg_0), atom_lookup.get(arg_1), nullptr, nullptr, nullptr)
	{

	}

	Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
		: Proposition_Instance(name, atom_lookup.get(arg_0), atom_lookup.get(arg_1), atom_lookup.get(arg_2), nullptr, nullptr)
	{

	}

	Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
		: Proposition_Instance(name, atom_lookup.get(arg_0), atom_lookup.get(arg_1), atom_lookup.get(arg_2), atom_lookup.get(arg_3), nullptr)
	{

	}

	Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
		: Proposition_Instance(name, atom_lookup.get(arg_0), atom_lookup.get(arg_1), atom_lookup.get(arg_2), atom_lookup.get(arg_3), atom_lookup.get(arg_4))
	{

	}

	Proposition_Instance::Proposition_Instance(const std::string& name, const Atom* arg_0, const Atom* arg_1, const Atom* arg_2, const Atom* arg_3, const Atom* arg_4)
		: name(name), arguments({ {arg_0, arg_1, arg_2, arg_3, arg_4} })
	{

	}
	std::string Proposition_Instance::to_hash() const
	{
		assert(id != EMPTY_INDEX);
		return std::to_string(id);
	}


	std::string Proposition_Instance::to_string() const
	{
		std::string result = name + "(";
		bool first = true;
		for (auto entry : arguments)
		{
			if (entry == nullptr)
			{
				continue;
			}

			if (first)
			{
				first = false;
			}
			else
			{
				result += ", ";
			}
			result += entry->get_name();
		}
		return result + ")";
	}

	size_t Proposition_Instance::get_id() const
	{
		return id;
	}

	bool Proposition_Instance::operator==(const Proposition_Instance& other) const
	{
		if (this->name != other.name || this->arguments.size() != other.arguments.size())
		{
			return false;
		}
		for (size_t i = 0; i < this->arguments.size(); i++)
		{
			if (this->arguments[i] != other.arguments[i])
			{
				return false;
			}
		}
		return true;
	}
	bool Proposition_Instance::operator!=(const Proposition_Instance& other) const
	{
		return !(*this == other);
	}

	bool Proposition_Instance::operator < (const Proposition_Instance& other) const
	{
		if (name < other.name) return true;
		if (name > other.name) return false;
		auto it1 = arguments.begin();
		auto it2 = other.arguments.begin();

		for (; it1 != arguments.end(); ++it1, ++it2)
		{
			if (*it1 == nullptr)
			{
				return *it2 != nullptr;
			}
			else if (*it2 == nullptr)
			{
				return false;
			}
			else if ((*it1)->get_id() < (*it2)->get_id())
			{
				return true;
			}
			else if ((*it1)->get_id() > (*it2)->get_id())
			{
				return false;
			}
		}
		return false;
	}

	//std::string Proposition_Instance::to_hash() const
	//{
	//	std::string hash = name;
	//	for (auto& arg : arguments)
	//	{
	//		if (arg != nullptr) hash += arg.id);
	//	}
	//	return hash;
	//}

	void Proposition_Instance::flood_null(size_t counter)
	{
		while (counter < PROPOSITION_LENGTH)
		{
			arguments[counter] = nullptr;
			++counter;
		}
	}
}