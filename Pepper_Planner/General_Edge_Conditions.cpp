#include "General_Edge_Conditions.hpp"
#include "Domain.hpp"
#include "Types.hpp"

namespace del 
{

	General_Edge_Condition::General_Edge_Condition(std::string event_from, std::string event_to, Formula&& condition) :
		event_from(event_from), event_to(event_to), condition(std::move(condition)) 
	{
	
	}

	void General_Edge_Conditions::insert(const General_Edge_Condition& edge_condition)
	{
		edge_conditions.push_back(edge_condition);
	}

	void General_Agent_Edge_Conditions::insert(Atom_Id agent, General_Edge_Conditions&& edge_conditions_input)
	{
		agent_edge_conditions.insert({ agent.id, std::move(edge_conditions_input) });
	}

	// TODO - Verify that this is actually called
	void General_Agent_Edge_Conditions::finalize(const Domain& domain, const std::vector<Atom_Id>& arguments) {
		std::unordered_set<std::string> seen_agents;

		for (auto&[agent_atom, edge_condition] : agent_edge_conditions) {
			if (agent_atom == REST_INDEX) {
				atom_to_agent.insert({ REST_INDEX, { } });
			}
			else
			{
				const Agent& agent = domain.get_agent_from_atom(arguments.at(agent_atom));
				seen_agents.insert(agent.get_name());
				atom_to_agent.insert({ agent_atom, { agent } });
			}
		}

		for (const Agent& agent : domain.get_agents()) {
			if (seen_agents.find(agent.get_name()) == seen_agents.end()) {
				atom_to_agent[REST_INDEX].push_back(agent);
			}
		}
	}

	size_t General_Agent_Edge_Conditions::size() const
	{
		return agent_edge_conditions.size();
	}

	void General_Agent_Edge_Conditions::convert_atom_to_id() const
	{
		for (const auto& [agent, agent_edge_conditions] : agent_edge_conditions)
		{

		}
	}
}