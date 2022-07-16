#pragma once

#include "Agents.hpp"
#include "General_Formula.hpp"
#include "Types.hpp"

#include <string>

namespace del
{

	class General_Edge_Condition 
	{
		friend struct Edge_Conditions;
	public:
		General_Edge_Condition();
		General_Edge_Condition(std::string event_from, std::string event_to, General_Formula&& condition);
	private:
		std::string event_from;
		std::string event_to;
		General_Formula condition;
	};

	class General_Edge_Conditions
	{
		friend struct Edge_Conditions;
	public:
		General_Edge_Conditions();
		void add(std::string event_from, std::string event_to, General_Formula&& condition);
	private:
		std::vector<General_Edge_Condition> edge_conditions;
	};

	// Edge conditions in general action, using input parameters (atoms)
	class General_Agent_Edge_Conditions
	{
		friend class Agent_Edge_Conditions;
	public:
		General_Agent_Edge_Conditions();
		void insert(const std::string& agent, General_Edge_Conditions& edge_conditions_input);
		size_t size() const;

	private:
		std::map<std::string, General_Edge_Conditions> agent_edge_conditions;
	};
}

