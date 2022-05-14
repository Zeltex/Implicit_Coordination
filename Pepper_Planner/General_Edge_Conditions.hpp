#pragma once

#include <string>
#include "Formula.hpp"
#include "Types.hpp"
#include "Agents.hpp"

namespace del
{
	class Domain;
	class General_Edge_Condition 
	{
		friend struct Edge_Conditions;
	public:
		General_Edge_Condition(std::string event_from, std::string event_to, Formula&& condition);
	private:
		std::string event_from;
		std::string event_to;
		Formula condition;
	};

	class General_Edge_Conditions
	{
		friend struct Edge_Conditions;
	public:
		void add(std::string event_from, std::string event_to, Formula&& condition);
	private:
		std::vector<General_Edge_Condition> edge_conditions;
	};

	// Edge conditions in general action, using input parameters (atoms)
	class General_Agent_Edge_Conditions
	{
		friend class Agent_Edge_Conditions;
	public:
		void insert(Atom_Id agent, General_Edge_Conditions& edge_conditions_input);
		//void finalize(const Domain& domain, const std::vector<Atom_Id>& arguments);
		size_t size() const;
		//void convert_atom_to_id() const;

	private:
		std::map<size_t, General_Edge_Conditions> agent_edge_conditions;

		// Atom input to domain agent mapping. Uses vector since _rest may map to multiple
		std::map<size_t, std::vector<Agent>> atom_to_agent;
	};
}

