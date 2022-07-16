#pragma once

#include "Types.hpp"
#include "Formula_Types.hpp"

#include <vector>

namespace del {
	class Atom;
	class Atom_Lookup;
	class General_Agent;
	class General_Agents;
	
	class Agent {
	public:
		Agent(const General_Agent& other, Agent_Id id, const Atom* atom);
		//Agent(Agent_Id id, Atom_Id atom_id, std::string name) : id(id), atom_id(atom_id), name(name) {}
		Agent_Id get_id() const;
		const Atom* get_atom() const;
		std::string get_name() const;
		std::string to_string() const;

		bool operator==(const Agent& other) const {
			return this->id == other.id;
		}

		bool operator<(const Agent& other) const {
			return this->id < other.id;
		}
	private:
		Agent_Id id;
		const Atom* atom;
		std::string name;
	};

	class Agents {
	public:
		Agents(const General_Agents& agents, const Atom_Lookup& atom_lookup);
		const Agent* get(size_t index) const;
		const Agent* get(Agent_Id id) const;
		const Agent* get(const std::string& name) const;
		const Agent* get(const Atom* atom) const;
		const std::vector<Agent>& get_all() const;
		size_t size() const;
		std::vector<Agent>::const_iterator begin() const;
		std::vector<Agent>::const_iterator end() const;
	private:
		std::vector<Agent> agents;
		std::map<const Atom*, const Agent*> atom_to_agent;
	};
}