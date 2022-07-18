#include "Propositions.hpp"

#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Converter_Base.hpp"
#include "Domain.hpp"
#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "Propositions_Lookup.hpp"

namespace del {

	Propositions::Propositions(const Propositions& other)
		: propositions(other.propositions)
	{

	}

	Propositions::Propositions()
		: propositions()
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

	void Propositions::insert(const Propositions& other)
	{
		for (const Proposition_Instance* proposition : other.propositions)
		{
			propositions.insert(proposition);
		}
	}

	void Propositions::insert(const Proposition_Instance* proposition)
	{
		propositions.insert(proposition);
	}

	void Propositions::remove(const Propositions& other)
	{
		for (const auto& proposition : other.propositions)
		{
			auto result = propositions.find(proposition);
			if (result != propositions.end())
			{
				propositions.erase(result);
			}
		}
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
}