#include "Accessibility_Relation.hpp"

#include "Domain.hpp"
#include "Action_Events.hpp"

namespace del 
{
	Accessibility_Relation::Accessibility_Relation(const Agent_Id& agent, size_t worlds_size)
		: agent(agent), worlds_size(worlds_size), world_relations(worlds_size * worlds_size, false)
	{
		
	}

	Accessibility_Relation::Accessibility_Relation(
		const Agent_Id& agent,
		const Accessibility_Relation& other, 
		const std::vector<World_Entry>& world_conversion,
		const Action& action,
		const Domain& domain,
		const State& state)
		: agent(agent), worlds_size(world_conversion.size()), world_relations(worlds_size * worlds_size, false)
	{
		for (const auto& from_conversion : world_conversion)
		{
			for (const auto& to_conversion : world_conversion)
			{
				if (!action.is_condition_fulfilled(agent, from_conversion.old_event, to_conversion.old_event, state, from_conversion.old_world, domain))
				{
					continue;
				}

				world_relations.at(get_index(from_conversion.new_world, to_conversion.new_world)) = other.has_direct_relation(from_conversion.old_world, from_conversion.old_world);
			}
		}
	}

	Accessibility_Relation::Accessibility_Relation(const Agent_Id& agent, const Accessibility_Relation& other, const std::map<World_Id, World_Id>& world_old_to_new)
		: agent(agent), worlds_size(world_old_to_new.size()), world_relations(worlds_size * worlds_size, false)
	{
		for (const auto&[world_old_from, world_new_from] : world_old_to_new) 
		{
			for (const auto& [world_old_to, world_new_to] : world_old_to_new)
			{
				world_relations.at(get_index(world_new_from, world_new_to)) = other.has_direct_relation(world_old_from, world_old_to);
			}
		}
	}

	bool Accessibility_Relation::is_serial_transitive_euclidean() const
	{
		for (size_t i = 0; i < worlds_size; ++i)
		{
			bool serial_connection_found = false;
			for (size_t j = 0; j < worlds_size; ++j)
			{
				if (!world_relations.at(get_index(i, j)))
				{
					continue;
				}

				serial_connection_found = true;

				for (size_t k = 0; k < worlds_size; ++k)
				{
					if (world_relations.at(get_index(j, k)) && !world_relations.at(get_index(i, k)))
					{
						// Not transitive
						return false;
					}

					if (world_relations.at(get_index(i, k)) && !world_relations.at(get_index(j, k)))
					{
						// Not euclidean
						return false;
					}
				}
			}

			if (!serial_connection_found) 
			{
				// Not serial
				return false;
			}
		}
		return true;
	}

	bool Accessibility_Relation::has_direct_relation(const World_Id& from_world, const World_Id& to_world) const 
	{
		return world_relations.at(get_index(from_world, to_world));
	}

	size_t Accessibility_Relation::get_index(const World_Id& from_world, const World_Id& to_world) const
	{
		return get_index(from_world.id, to_world.id);
	}
	
	size_t Accessibility_Relation::get_index(const size_t& from_world, const size_t& to_world) const
	{
		return from_world * worlds_size + to_world;
	}


	bool Accessibility_Relation::operator== (const Accessibility_Relation& other) const
	{
		if (this->worlds_size != other.worlds_size || world_relations.size() != other.world_relations.size())
		{
			return false;
		}

		for (size_t i = 0; i < world_relations.size(); i++)
		{
			if (world_relations.at(i) != other.world_relations.at(i))
			{
				return false;
			}
		}

		return true;
	}

	bool Accessibility_Relation::operator!= (const Accessibility_Relation& other) const
	{
		return !(*this == other);
	}

	void Accessibility_Relation::to_hashable_string(std::string& ref_result, size_t& ref_count) const
	{
		for (size_t i = 0; i < world_relations.size(); i++)
		{
			if (world_relations.at(i))
			{
				++ref_count;
				ref_result += std::to_string(i);
			}
		}
	}

	std::string Accessibility_Relation::to_string(const Domain& domain) const
	{
		std::string result;
		bool first = true;
		for (size_t world_from = 0; world_from < worlds_size; ++world_from)
		{
			for (size_t world_to = 0; world_to < worlds_size; ++world_to)
			{
				if (world_relations.at(get_index({ world_from }, { world_to })))
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
						+ domain.get_agent(agent).get_name() + ", "
						+ std::to_string(world_from) + ", "
						+ std::to_string(world_to) + ")";
				}
			}
		}
		return result;
	}

	void Accessibility_Relation::set(World_Id world_from, World_Id world_to)
	{
		world_relations.at(get_index(world_from, world_to)) = true;
	}

	// ------

	
	Accessibility_Relations::Accessibility_Relations(const std::vector<Accessibility_Relation>& new_agent_relations)
		: worlds_size(new_agent_relations.size()), agent_relations(new_agent_relations)
	{
	}


	Accessibility_Relations::Accessibility_Relations(size_t world_count, size_t agent_count)
		: worlds_size(world_count), agent_relations()
	{
		for (size_t i = 0; i < agent_count; ++i)
		{
			agent_relations.push_back(Accessibility_Relation(Agent_Id{ i }, world_count));
		}

		// TODO
	}

	void Accessibility_Relations::convert_world_ids(const std::map<World_Id, World_Id>& world_old_to_new)
	{
		std::vector<Accessibility_Relation> new_agent_relations;
		for (size_t i = 0; i < agent_relations.size(); ++i)
		{
			new_agent_relations.push_back(Accessibility_Relation(Agent_Id{ i }, agent_relations.at(i), world_old_to_new));
		}
		agent_relations = new_agent_relations;
	}
	std::set<World_Id> Accessibility_Relations::get_unreachable_worlds(const std::set<World_Id>& worlds) const
	{
		std::set<World_Id> unreachable_worlds;
		std::vector<World_Id> frontier;
		frontier.assign(worlds.begin(), worlds.end());

		size_t prev_size = 0;
		size_t new_size = frontier.size();
		while (prev_size != new_size && new_size != 0)
		{
			World_Id world = frontier.back();
			frontier.pop_back();
			for (const Accessibility_Relation& agent_relation : agent_relations) 
			{
				for (size_t i = 0; i < worlds_size; ++i)
				{
					size_t to_world = world.id * worlds_size + i;
					if (agent_relation.world_relations.at(i)
						&& unreachable_worlds.find(World_Id{ to_world }) != unreachable_worlds.end())
					{
						unreachable_worlds.erase(World_Id{ to_world });
						frontier.push_back(World_Id{ to_world });
					}
				}
			}
		}
		return unreachable_worlds;
	}
	
	bool Accessibility_Relations::has_direct_relation(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const
	{
		return agent_relations.at(agent.id).has_direct_relation(from_world, to_world);
	}

	Accessibility_Relations Accessibility_Relations::product_update(
		const std::vector<World_Entry>& world_conversion,
		const Action& action,
		const Domain& domain,
		const State& state) const
	{
		std::vector<Accessibility_Relation> new_agent_relations;
		for (size_t i = 0; i < agent_relations.size(); ++i)
		{
			new_agent_relations.push_back(Accessibility_Relation(Agent_Id{ i }, agent_relations.at(i), world_conversion, action, domain, state));
		}
		return Accessibility_Relations(new_agent_relations);
	}
	
	bool Accessibility_Relations::operator== (const Accessibility_Relations& other) const
	{
		if (agent_relations.size() != other.agent_relations.size())
		{
			return false;
		}

		auto it1 = agent_relations.begin();
		auto it2 = other.agent_relations.begin();

		for (; it1 != agent_relations.end(); ++it1, ++it2)
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
		std::string result;
		for (size_t i = 0; i < agent_relations.size(); ++i)
		{
			result += std::to_string(i);
			agent_relations.at(i).to_hashable_string(result, ref_count);
		}

		return result;
	}

	std::string Accessibility_Relations::to_string(const Domain& domain) const
	{
		std::string result;
		bool first = true;
		for (size_t i = 0; i < agent_relations.size(); ++i)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				result += "\n";
			}
			result += agent_relations.at(i).to_string(domain);
		}
		return result;
	}

	bool Accessibility_Relations::is_serial_transitive_euclidean() const
	{
		for (const Accessibility_Relation& agent_relation : agent_relations)
		{
			if (!agent_relation.is_serial_transitive_euclidean())
			{
				return false;
			}
		}
		return true;
	}

	void Accessibility_Relations::set(Agent_Id agent, World_Id world_from, World_Id world_to)
	{
		agent_relations.at(agent.id).set(world_from, world_to);
	}
}