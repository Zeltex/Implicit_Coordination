#pragma once
#include "World.hpp"
#include "General_World.hpp"

namespace del {

	class General_Agents;
	class Inputs_Buffer;
	class Proposition_Instance_Buffer;
	class Variables_Buffer;

	class General_State
	{
	friend class State;
	public:
		General_State();
		void add_world(const std::string& name, Proposition_Instance_Buffer& proposition_instance_buffer);

		void set_designated_worlds(Variables_Buffer& variables_buffer);
		void set_single_designated_world(World_Id world);
		
		void add_accessibility_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_accessibility_relations(const std::string& agent_name, Inputs_Buffer& inputs_buffer, const General_Agents& general_agents);
		
		const std::vector<General_World>& get_worlds() const;
		World_Id get_world_id(const std::string& name) const;

	private:

		size_t cost;
		std::vector<General_World> worlds;
		std::set<World_Id> designated_worlds;
		std::vector<Agent_World_Relation> agent_world_relations;
	};
}