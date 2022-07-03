#include "Propositions.hpp"

#include "Atoms.hpp"
#include "Domain.hpp"
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

	Propositions::Propositions(const Proposition_Instance_Buffer& rigid_propositions, const Propositions_Lookup& propositions_lookup)
	{
		for (const Proposition_Instance& instance : rigid_propositions.proposition_instances)
		{
			propositions.insert(propositions_lookup.get(instance));
		}
	}

	Propositions::Propositions(const std::vector<Proposition_Instance>& other, const Propositions_Lookup& propositions_lookup, const Atoms& arguments)
	{
		for (const Proposition_Instance& instance : other)
		{
			Proposition_Instance grounded_instance{ instance, arguments };
			propositions.insert(propositions_lookup.get(grounded_instance));
		}
	}

	void Propositions::insert(const Propositions& other)
	{
		for (const Proposition& proposition : other.propositions)
		{
			propositions.insert(proposition);
		}
	}

	void Propositions::insert(const Proposition& proposition)
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

	bool Propositions::contains(const Proposition& proposition) const
	{
		return propositions.find(proposition) != propositions.end();
	}

	std::string Propositions::to_string(const Domain& domain) const
	{
		std::string result;
		for (const Proposition& proposition : propositions)
		{
			result += ", " + domain.get_proposition_instance(proposition).to_string(domain);
		}
		return result;
	}

	std::string Propositions::to_signature_string() const
	{
		std::string result;
		for (const Proposition& proposition : propositions)
		{
			result += proposition.to_string();
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
		std::set<Proposition>::const_iterator props1 = propositions.begin();
		std::set<Proposition>::const_iterator props2 = other.propositions.begin();

		for (; props1 != propositions.end(); ++props1, ++props2) 
		{
			if (*props1 != *props2) return true;
		}
		return false;
	}

	std::string Propositions::to_hash() const
	{
		std::string hash;
		for (const Proposition& prop : propositions)
		{
			hash += prop.to_hash();
		}
		return hash;
	}
}