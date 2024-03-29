#include "General_Edge_Conditions.hpp"

#include "Domain.hpp"
#include "Types.hpp"

namespace del 
{
	General_Edge_Condition::General_Edge_Condition()
		: event_from(), event_to(), condition()
	{

	}

	General_Edge_Condition::General_Edge_Condition(std::string event_from, std::string event_to, General_Formula&& condition) :
		event_from(event_from), event_to(event_to), condition(std::move(condition)) 
	{
	
	}

	General_Edge_Conditions::General_Edge_Conditions()
		: edge_conditions()
	{

	}

	void General_Edge_Conditions::add(std::string event_from, std::string event_to, General_Formula&& condition)
	{
		edge_conditions.push_back(General_Edge_Condition{ event_from, event_to, std::move(condition) });
	}

	General_Agent_Edge_Conditions::General_Agent_Edge_Conditions()
		: agent_edge_conditions()
	{

	}

	void General_Agent_Edge_Conditions::insert(const std::string& agent, General_Edge_Conditions& edge_conditions_input)
	{
		agent_edge_conditions.insert({ agent, std::move(edge_conditions_input) });
		edge_conditions_input = {};
	}

	size_t General_Agent_Edge_Conditions::size() const
	{
		return agent_edge_conditions.size();
	}
}