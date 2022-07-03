#include "Converter.hpp"

#include <assert.h>

namespace del 
{

	void Converter::set(const Proposition& from, const Proposition& to)
	{
		propositions.insert({ from, to });
	}

	void Converter::set(const Agent_Id& from, const Agent_Id& to)
	{
		agents.insert({ from, to });
	}

	Proposition Converter::convert(const Proposition& from) const
	{
		return propositions.at(from);
	}

	Agent_Id Converter::convert(const Agent_Id& from) const
	{
		assert(agents.find(from) != agents.end());
		return agents.at(from);
	}
}