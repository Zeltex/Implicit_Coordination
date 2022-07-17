#pragma once
#include <vector>
#include <set>
#include <string>

namespace del
{
	class Inputs_Buffer;
	class Inputs;

	// E.g. at(agent, pos)
	// name="agent", type_inputs={"agent", "pos"}
	class General_Typed_Proposition
	{
	friend class Propositions_Lookup;
	friend class General_Typed_Propositions;
	public:
		General_Typed_Proposition(const std::string& name, std::vector<std::string> type_inputs);
	private:
		std::string name;
		std::vector<std::string> type_inputs;
	};

	class General_Typed_Propositions
	{
	private:
		struct Comparator
		{
			bool operator()(const General_Typed_Proposition& lhs, const General_Typed_Proposition rhs) const
			{
				return lhs.name < rhs.name;
			}
		};
	public:
		void add(const std::string& name, Inputs_Buffer& inputs_buffer);
		std::set<General_Typed_Proposition>::const_iterator begin() const;
		std::set<General_Typed_Proposition>::const_iterator end() const;
	private:
		std::set<General_Typed_Proposition, Comparator> propositions;
	};
}