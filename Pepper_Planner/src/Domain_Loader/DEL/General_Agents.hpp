#pragma once

#include "Types.hpp"
#include "Formula_Types.hpp"

#include <vector>

namespace del {
	class General_Objects;
	class General_Agent {
	friend class Agent;
	public:
		General_Agent(Agent_Id id, Atom_Id atom_id, const std::string& name);
		Agent_Id get_id() const;
		Atom_Id get_atom_id() const;
		const std::string& get_name() const;
	private:
		Agent_Id id;
		Atom_Id atom_id;
		std::string name;
	};

	class General_Agents {
	public:
		General_Agents();
		const General_Agent& get(const std::string& name) const;
		const General_Agent& get(const Agent_Id& agent_id) const;
		void set(const std::vector<std::string>& agent_names, General_Objects& objects);
		std::vector<General_Agent>::const_iterator begin() const;
		std::vector<General_Agent>::const_iterator end() const;
	private:
		std::vector<General_Agent> agents;
	};
}