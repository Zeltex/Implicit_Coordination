#pragma once
#include "World.hpp"
#include "General_World.hpp"

namespace del {

	class Variables_Buffer;
	class Inputs_Buffer;
	class Proposition_Instance_Buffer;
	class General_State
	{
	public:
		General_State();
		void add_world(const std::string& name, Proposition_Instance_Buffer& proposition_instance_buffer);

		void set_cost(size_t cost);
		void set_designated_worlds(Variables_Buffer& variables_buffer);
		void set_single_designated_world(World_Id world);
		
		void add_accessibility_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_accessibility_relation(const std::string& agent_name, Inputs_Buffer& inputs_buffer);
		
		const std::vector<General_World>& get_worlds() const;
		World_Id get_world_id(const std::string& name) const;
		Agent_Id get_agent_id(const std::string& name)const;

		State to_state();

	private:

		size_t cost;
		std::vector<General_World> worlds;
		std::set<World_Id> designated_worlds;
		std::vector<Agent_World_Relation> agent_world_relations;
		//Accessibility_Relations accessibility_relations;
	};
}