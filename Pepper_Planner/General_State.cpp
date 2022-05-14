#include "General_State.hpp"
#include "Variables_Buffer.hpp"
#include "Inputs_Buffer.hpp"
#include "General_Action_Events.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "General_World.hpp"

#include <exception>

namespace del {

	General_State::General_State()
	{

	}

	void General_State::add_world(const std::string& name, Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		World_Id world_id{ worlds.size() };
		// TODO - Verify that this should not be transformed
		std::vector<Proposition_Instance> proposition = proposition_instance_buffer.get();
		worlds.push_back(General_World(name, world_id, std::move(proposition)));
	}

	void General_State::set_cost(size_t cost) {
		this->cost = cost;
	}

	void General_State::set_single_designated_world(World_Id world) {
		designated_worlds.clear();
		designated_worlds.insert(world);
	}

	void General_State::set_designated_worlds(Variables_Buffer& variables_buffer)
	{
		std::vector<std::string> worlds = variables_buffer.get();
		for (const std::string& world : worlds)
		{
			designated_worlds.insert(get_world_id(world));
		}
	}

	World_Id General_State::get_world_id(const std::string& name) const
	{
		for (const General_World& world : worlds)
		{
			if (world.get_name() == name)
			{
				return world.get_id();
			}
		}
		throw "Unknown world " + name;
	}

	void General_State::add_accessibility_relation(Agent_Id agent, World_Id world_from, World_Id world_to)
	{
		agent_world_relations.push_back({ agent, world_from, world_to });
	}

	void General_State::add_accessibility_relation(const std::string& agent_name, Inputs_Buffer& inputs_buffer)
	{
		Inputs inputs = inputs_buffer.get();
		if (inputs.size() != 1)
		{
			throw "Reachability had input size " + inputs.size();
		}
		Input input = inputs.get(0);

		const std::string& world_from = input.get_type();
		const std::string& world_to = input.get_name();
		
		add_accessibility_relation(get_agent_id(agent_name), get_world_id(world_from), get_world_id(world_to));
	}

	const std::vector<General_World>& General_State::get_worlds() const
	{
		return worlds;
	}
}