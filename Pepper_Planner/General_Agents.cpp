
#include "General_Agents.hpp"
#include "General_Objects.hpp"
namespace del
{
	General_Agent::General_Agent(Agent_Id id, Atom_Id atom_id, const std::string& name)
		: id(id), atom_id(atom_id), name(name)
	{

	}

	Agent_Id General_Agent::get_id() const
	{
		return id;
	}

	Atom_Id General_Agent::get_atom_id() const
	{
		return atom_id;
	}

	const std::string& General_Agent::get_name() const
	{
		return name;
	}

	General_Agents::General_Agents()
	{
	
	}

	void General_Agents::set(const std::vector<std::string>& agent_names, General_Objects& objects)
	{
		for (const std::string& agent : agent_names)
		{
			Atom_Id atom_id = objects.get_atom_id(agent);
			Agent_Id agent_id{ agents.size() };
			agents.push_back({ agent_id, atom_id, agent });
		}
	}

	std::vector<General_Agent>::const_iterator General_Agents::begin() const
	{
		return agents.begin();
	}

	std::vector<General_Agent>::const_iterator General_Agents::end() const
	{
		return agents.end();
	}

	const General_Agent& General_Agents::get(const std::string& name) const
	{
		for (const General_Agent& agent : agents) 
		{
			if (agent.get_name() == name)
			{
				return agent;
			}
		}
		throw "Unknown agent " + name;
	}

	const General_Agent& General_Agents::get(const Agent_Id& agent_id) const
	{
		return agents.at(agent_id.id);
	}
}