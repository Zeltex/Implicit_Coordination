#include "General_Edge_Conditions.hpp"
#include "Domain.hpp"
#include "Types.hpp"

namespace del 
{

	General_Edge_Condition::General_Edge_Condition(std::string event_from, std::string event_to, Formula&& condition) :
		event_from(event_from), event_to(event_to), condition(std::move(condition)) 
	{
	
	}

	void General_Edge_Conditions::add(std::string event_from, std::string event_to, Formula&& condition)
	{
		edge_conditions.push_back(General_Edge_Condition{ event_from, event_to, std::move(condition) });
	}

	void General_Agent_Edge_Conditions::insert(Atom_Id agent, General_Edge_Conditions& edge_conditions_input)
	{
		agent_edge_conditions.insert({ agent.id, std::move(edge_conditions_input) });
		edge_conditions_input = {};
	}

	size_t General_Agent_Edge_Conditions::size() const
	{
		return agent_edge_conditions.size();
	}
}