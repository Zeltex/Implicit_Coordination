#pragma once

#include "Types.hpp"
#include "Formula_Types.hpp"

#include <vector>

namespace del {
	class General_Agent;
	class General_Agents;
	class Agent {
	public:
		Agent(const General_Agent& other);
		Agent(Agent_Id id, Atom_Id atom_id, std::string name) : id(id), atom_id(atom_id), name(name) {}
		Agent_Id get_id() const;
		Atom_Id get_atom_id() const;
		std::string get_name() const;

		bool operator==(const Agent& other) const {
			return this->id == other.id;
		}

		bool operator<(const Agent& other) const {
			return this->id < other.id;
		}
	private:
		Agent_Id id;
		Atom_Id atom_id;
		std::string name;
	};

	class Agents {
	public:
		Agents(const General_Agents& agents);
		const Agent& get(const std::string& name) const;
		const Agent& get(const Agent_Id& agent_id) const;
		const Agent& get(const Atom_Id& atom_id) const;
		const std::vector<Agent>& get_all() const;
		size_t size() const;
		std::vector<Agent>::const_iterator begin() const;
		std::vector<Agent>::const_iterator end() const;
	private:
		std::vector<Agent> agents;
	};
}