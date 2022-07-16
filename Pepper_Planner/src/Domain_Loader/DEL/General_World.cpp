#include "General_World.hpp"

namespace del {


	General_World::General_World(const std::string& name, World_Id world_id, std::vector<General_Proposition_Instance> propositions)
		: name(name), world_id(world_id), propositions(propositions) 
	{
	
	}

	const std::string& General_World::get_name() const
	{
		return name;
	}

	World_Id General_World::get_id() const
	{
		return world_id;
	}
}