#pragma once

#include "Propositions.hpp"
#include "Types.hpp"

#include <map>

namespace del 
{
	class Converter
	{
	public:
		void set(const Proposition& from, const Proposition& to);
		void set(const Agent_Id& from, const Agent_Id& to);
		Proposition convert(const Proposition& from) const;
		Agent_Id convert(const Agent_Id& from) const;
	private:
		std::map<Proposition, Proposition> propositions;
		std::map<Agent_Id, Agent_Id> agents;
	};
}