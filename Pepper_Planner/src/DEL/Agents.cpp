#include "Agents.hpp"

#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "General_Agents.hpp"

#include <iostream>
#include <assert.h>

namespace del 
{
	Agent::Agent(const General_Agent& other, Agent_Id id, const Atom* atom)
		: name(other.name), id(id), atom(atom)
	{
	
	}

	Agent_Id Agent::get_id() const {
		return id;
	}

	const Atom* Agent::get_atom() const {
		return atom;
	}

	std::string Agent::get_name() const {
		return name;
	}

	std::string Agent::to_string() const
	{
		return name;
	}

	Agents::Agents(const General_Agents& other, const Atom_Lookup& atom_lookup)
	{
		Agent_Id id = 0;
		for (const General_Agent& agent : other)
		{
			agents.emplace_back(agent, id, atom_lookup.get(agent.get_name()));
			++id;
		}

		for (const Agent& agent : agents)
		{
			atom_to_agent.insert({ atom_lookup.get(agent.get_name()), &agent });
		}
	}

	const Agent* Agents::get(size_t index) const
	{
		return &agents.at(index);
	}

	const Agent* Agents::get(Agent_Id id) const
	{
		return &agents.at(id.id);
	}

	const Agent* Agents::get(const std::string& name) const
	{
		for (const Agent& entry : agents) {
			if (entry.get_name() == name) {
				return &entry;
			}
		}
		assert(false);
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
	}

	const Agent* Agents::get(const Atom* atom) const
	{
		auto it = atom_to_agent.find(atom);
		assert(it != atom_to_agent.end());
		return it->second;
	}

	const std::vector<Agent>& Agents::get_all() const
	{
		return agents;
	}

	size_t Agents::size() const
	{
		return agents.size();
	}

	std::vector<Agent>::const_iterator Agents::begin() const
	{
		return agents.begin();
	}

	std::vector<Agent>::const_iterator Agents::end() const
	{
		return agents.end();
	}

}