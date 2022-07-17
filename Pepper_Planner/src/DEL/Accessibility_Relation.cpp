#include "Accessibility_Relation.hpp"

#include <assert.h>

#include "Action_Events.hpp"
#include "Agents.hpp"
#include "Domain.hpp"


namespace del 
{

	Accessibility_Relations::Accessibility_Relations(size_t world_count, const Agents* agents)
		: worlds_size(world_count), worlds_size_squared(world_count * world_count), agents(agents), relations(agents->size() * world_count * world_count)
	{
	}
	
	Accessibility_Relations::Accessibility_Relations(std::vector<bool>&& new_agent_relations, size_t world_count, const Agents* agents)
		: worlds_size(world_count), worlds_size_squared(world_count * world_count), agents(agents), relations(std::move(new_agent_relations))
	{

	}

	size_t Accessibility_Relations::get_index(const size_t& agent, const size_t& from_world, const size_t& to_world) const
	{

		return agent * worlds_size_squared + from_world * worlds_size + to_world;
	}

	size_t Accessibility_Relations::get_index(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const
	{

		return get_index(agent.id, from_world.id, to_world.id);
	}

	size_t Accessibility_Relations::get_index(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world, const size_t worlds_size, const size_t worlds_size_squared) const
	{
		return agent.id * worlds_size_squared + from_world.id * worlds_size + to_world.id;
	}

	void Accessibility_Relations::convert_world_ids(const std::map<World_Id, World_Id>& world_old_to_new)
	{
		std::vector<bool> new_relations(relations.size(), false);
		size_t agents_size = agents->size();
		for (size_t agent = 0; agent < agents_size; ++agent)
		{
			for (const auto& [world_old_from, world_new_from] : world_old_to_new)
			{
				for (const auto& [world_old_to, world_new_to] : world_old_to_new)
				{
					new_relations.at(get_index(agent, world_new_from.id, world_new_to.id)) = relations.at(get_index(agent, world_old_from.id, world_old_to.id));
				}
			}
		}
		relations = std::move(new_relations);
	}

	std::set<World_Id> Accessibility_Relations::get_unreachable_worlds(const std::set<World_Id>& worlds) const
	{
		std::set<World_Id> unreachable_worlds;
		std::vector<World_Id> frontier;
		frontier.assign(worlds.begin(), worlds.end());

		size_t agents_size = agents->size();
		while (!frontier.empty())
		{
			World_Id from_world = frontier.back();
			frontier.pop_back();
			for (Agent_Id agent = 0; agent < agents_size; ++agent)
			{
				for (World_Id to_world = 0; to_world < worlds_size; ++to_world)
				{
					World_Id relations_index = get_index(agent, from_world, to_world);
					assert(relations_index.id < relations.size());
					if (relations.at(relations_index.id) && unreachable_worlds.find(to_world) != unreachable_worlds.end())
					{
						unreachable_worlds.erase(to_world);
						frontier.push_back(to_world);
					}
				}
			}
		}
		return unreachable_worlds;
	}
	
	bool Accessibility_Relations::has_direct_relation(Agent_Id agent, const World_Id& from_world, const World_Id& to_world) const
	{
		assert(agent.id < agents->size());
		return relations.at(get_index(agent, from_world, to_world));
	}

	bool Accessibility_Relations::has_direct_relation(const Agent* agent, const World_Id& from_world, const World_Id& to_world) const
	{
		assert(agent != nullptr);
		return has_direct_relation(agent->get_id(), from_world, to_world);
	}

	Accessibility_Relations Accessibility_Relations::product_update(
		const std::vector<World_Entry>& world_conversion,
		const Action* action,
		const Domain& domain,
		const State& state,
		const size_t& new_worlds_size) const
	{

		size_t new_worlds_size_squared = new_worlds_size * new_worlds_size;

		size_t agents_size = agents->size();
		std::vector<bool> result(agents_size * new_worlds_size * new_worlds_size, false);
		for (Agent_Id agent = 0; agent < agents_size; ++agent)
		{
			for (const World_Entry& from_conversion : world_conversion)
			{
				for (const World_Entry& to_conversion : world_conversion)
				{
					if (!action->is_condition_fulfilled(agent, from_conversion.old_event, to_conversion.old_event, state, from_conversion.old_world, domain))
					{
						continue;
					}

					if (!has_direct_relation(agent, from_conversion.old_world, to_conversion.old_world))
					{
						continue;
					}
					
					size_t index = get_index(agent, from_conversion.new_world, to_conversion.new_world, new_worlds_size, new_worlds_size_squared);

					assert(index < result.size());
					result.at(index) = true;
				}
			}
		}
		return Accessibility_Relations(std::move(result), new_worlds_size, agents);
	}
	
	bool Accessibility_Relations::operator== (const Accessibility_Relations& other) const
	{
		if (relations.size() != other.relations.size())
		{
			return false;
		}

		auto it1 = relations.begin();
		auto it2 = other.relations.begin();

		for (; it1 != relations.end(); ++it1, ++it2)
		{
			if (*it1 != *it2)
			{
				return false;
			}
		}
		return true;
	}

	bool Accessibility_Relations::operator!= (const Accessibility_Relations& other) const
	{
		return !(*this == other);
	}

	std::string Accessibility_Relations::to_hashable_string(size_t& ref_count) const
	{
		std::string result = std::to_string(agents->size()) + std::to_string(worlds_size);
		size_t count = 0;
		for (const bool& relation : relations)
		{
			if (relation)
			{
				++ref_count;
				result += std::to_string(count);
			}
			++count;
		}
		return result;
	}

	std::string Accessibility_Relations::to_string() const
	{
		std::string result;
		bool first = true;
		size_t index = 0;
		for (auto& agent : *agents)
		{
			for (size_t world_from = 0; world_from < worlds_size; ++world_from)
			{
				for (size_t world_to = 0; world_to < worlds_size; ++world_to)
				{
					assert(index == get_index(agent.get_id(), world_from, world_to));
					if (relations.at(index))
					{
						if (first)
						{
							first = false;
						}
						else
						{
							result += "\n";
						}
						result += "("
							+ agent.get_name() + ", "
							+ std::to_string(world_from) + ", "
							+ std::to_string(world_to) + ")";
					}
					++index;
				}
			}
		}


		return result;
	}

	bool Accessibility_Relations::is_serial_transitive_euclidean() const
	{
		size_t index = 0;
		size_t agents_size = agents->size();
		for (Agent_Id agent = 0; agent < agents_size; ++agent)
		{
			for (World_Id world_from = 0; world_from < worlds_size; ++world_from)
			{
				bool serial_connection_found = false;
				for (World_Id world_to = 0; world_to < worlds_size; ++world_to)
				{
					assert(index == get_index(agent, world_from, world_to));
					if (!relations.at(index))
					{
						++index;
						continue;
					}

					serial_connection_found = true;

					for (size_t world_extra = 0; world_extra < worlds_size; ++world_extra)
					{
						if (relations.at(get_index(agent, world_to, world_extra)) && !relations.at(get_index(agent, world_from, world_extra)))
						{
							// Not transitive
							return false;
						}

						if (relations.at(get_index(agent, world_from, world_extra)) && !relations.at(get_index(agent, world_to, world_extra)))
						{
							// Not euclidean
							return false;
						}
					}
					++index;
				}

				if (!serial_connection_found)
				{
					// Not serial
					return false;
				}
			}
		}
		return true;
	}

	void Accessibility_Relations::set(Agent_Id agent, World_Id world_from, World_Id world_to)
	{
		relations.at(get_index(agent, world_from, world_to)) = true;
	}

	const Agents* Accessibility_Relations::get_agents() const
	{
		return agents;
	}
}