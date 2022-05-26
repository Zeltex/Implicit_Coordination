#include "Agents.hpp"
#include "General_Agents.hpp"

#include <iostream>
#include <assert.h>

namespace del 
{
	Agent::Agent(const General_Agent& other)
	{
		atom_id = other.atom_id;
		id = other.id;
		name = other.name;
	}

	Agent_Id Agent::get_id() const {
		return id;
	}

	Atom_Id Agent::get_atom_id() const {
		return atom_id;
	}

	std::string Agent::get_name() const {
		return name;
	}

	Agents::Agents(const General_Agents& other)
	{
		for (const General_Agent& agent : other)
		{
			agents.push_back(Agent(agent));
		}
	}

	const Agent& Agents::get(const std::string& name) const
	{
		for (auto& entry : agents) {
			if (entry.get_name() == name) {
				return entry;
			}
		}
		assert(false);
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
	}

	const Agent& Agents::get(const Agent_Id& agent_id) const
	{
		return agents.at(agent_id.id);
	}

	const Agent& Agents::get(const Atom_Id& atom_id) const
	{
		for (auto& entry : agents) {
			if (entry.get_atom_id() == atom_id) {
				return entry;
			}
		}
		assert(false);
	}

	const std::vector<Agent>& Agents::get_all() const
	{
		return agents;
	}

	size_t Agents::size() const
	{
		return agents.size();
	}
}