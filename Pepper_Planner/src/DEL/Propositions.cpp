#include "Propositions.hpp"

#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Converter_Base.hpp"
#include "Domain.hpp"
#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "Propositions_Lookup.hpp"

namespace del {

	Propositions::Propositions(const Propositions& other, const Propositions& delete_list, const Propositions& add_list)
		: propositions(other.propositions)
	{
		for (const auto& proposition : delete_list.propositions)
		{
			auto result = propositions.find(proposition);
			if (result != propositions.end())
			{
				propositions.erase(result);
			}
		}

		for (const Proposition_Instance* proposition : add_list.propositions)
		{
			propositions.insert(proposition);
		}
	}

	Propositions::Propositions(const Propositions& other)
		: propositions(other.propositions)
	{

	}

	Propositions::Propositions(const std::vector<General_Proposition_Instance>& other, const Converter_Base* converter)
	{
		for (auto& general_instance : other)
		{
			propositions.insert(converter->convert(&general_instance));
		}
	}

	Propositions::Propositions(const Proposition_Instance_Buffer& other, const Converter_Base* converter)
		: Propositions(other.proposition_instances, converter)
	{

	}

	Propositions::Propositions(std::set<const Proposition_Instance*, Comparator> data_in)
		: propositions(std::move(data_in))
	{

	}

	Propositions Propositions::combine(const Propositions& other) const
	{
		auto new_propositions = propositions;
		for (auto& prop : other)
		{
			new_propositions.insert(prop);
		}
		return Propositions(new_propositions);
	}

	bool Propositions::contains(const Proposition_Instance* proposition) const
	{
		return propositions.find(proposition) != propositions.end();
	}

	std::string Propositions::to_string() const
	{
		std::string result;
		for (const Proposition_Instance* proposition : propositions)
		{
			result += ", " + proposition->to_string();
		}
		return result;
	}

	std::string Propositions::to_signature_string() const
	{
		std::string result;
		for (const Proposition_Instance* proposition : propositions)
		{
			result += std::to_string(proposition->get_id());
		}
		return result;
	}

	size_t Propositions::size() const
	{
		return propositions.size();
	}

	bool Propositions::operator!=(const Propositions& other) const
	{
		if (propositions.size() != other.propositions.size()) return true;
		std::set<const Proposition_Instance*>::const_iterator props1 = propositions.begin();
		std::set<const Proposition_Instance*>::const_iterator props2 = other.propositions.begin();

		for (; props1 != propositions.end(); ++props1, ++props2) 
		{
			if (*props1 != *props2)
			{
				return true;
			}
		}
		return false;
	}

	std::string Propositions::to_hash() const
	{
		std::string hash;
		for (const Proposition_Instance* prop : propositions)
		{
			hash += prop->to_hash();
		}
		return hash;
	}

	std::set<const Proposition_Instance*, Propositions::Comparator>::const_iterator Propositions::begin() const
	{
		return propositions.begin();
	}

	std::set<const Proposition_Instance*, Propositions::Comparator>::const_iterator Propositions::end() const
	{
		return propositions.end();
	}
}