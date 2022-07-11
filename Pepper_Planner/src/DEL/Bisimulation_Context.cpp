#include "Bisimulation_Context.hpp"
#include "Core.hpp"
#include "Types.hpp"
#include "General_State.hpp"

#include <set>
#include <map>
#include <algorithm>
#include <deque>

namespace del::bisimulation_context {

	struct Block_Id {
		size_t id;
		World_Id to_world() const { return World_Id{ id }; }
		bool operator==(const Block_Id& other) const { return this->id == other.id; }
		bool operator!=(const Block_Id& other) const { return this->id != other.id; }
		bool operator<(const  Block_Id& other) const { return this->id < other.id; }
		bool operator>(const  Block_Id& other) const { return this->id > other.id; }
	};

	struct Agent_World_Reachable
	{
		Agent_Id agent;
		const World* world;

		bool operator!= (const Agent_World_Reachable& other) const
		{
			return agent != other.agent && world != other.world;
		}

		//bool operator< (const Agent_World_Reachable& other) const
		//{
		//	if (agent != other.agent) return agent < other.agent;
		//	if (*world != *other.world) return *world < *other.world;
		//	return false;
		//}
	};

	struct Agent_Block_Reachable
	{
		Agent_Id agent;
		Block_Id block;

		bool operator!= (const Agent_Block_Reachable& other) const 
		{
			return agent != other.agent && block != other.block;
		}

		bool operator< (const Agent_Block_Reachable& other) const
		{
			if (agent != other.agent) return agent < other.agent;
			if (block != other.block) return block < other.block;
			return false;
		}
	};

	struct Signature
	{
		void insert(const Agent_Block_Reachable& agent_block_reachable)
		{
			agent_block_reachables.insert(agent_block_reachable);
		}

		bool operator!=(const Signature& other) const
		{
			return !(*this == other);
		}

		bool operator==(const Signature& other) const
		{
			return !(*this < other || other < *this);
		}

		bool operator<(const Signature& other) const
		{
			if (agent_block_reachables.size() != other.agent_block_reachables.size()) 
			{
				return agent_block_reachables.size() < other.agent_block_reachables.size();
			}

			auto it1 = agent_block_reachables.begin();
			auto it2 = other.agent_block_reachables.begin();
			for (; it1 != agent_block_reachables.end(); ++it1, ++it2) 
			{
				if (*it1 != *it2)
				{
					return *it1 < *it2;
				}
			}
			return false;
		}
		
		std::set<Agent_Block_Reachable> agent_block_reachables;
	};

	bool compare_worlds(const World* a, const World* b) {
		return a < b;
	}

	struct Block 
	{
		Block()
			: worlds(compare_worlds)
		{

		}

		void insert(const World* world) 
		{
			worlds.insert(world);
		}

		void remove(const World* world) 
		{
			worlds.erase(std::find(worlds.begin(), worlds.end(), world));
		}

		Propositions get_propositions() const
		{
			Propositions propositions = (*worlds.begin())->get_true_propositions();
			return propositions;
		}

		std::set<const World*, decltype(compare_worlds)*> worlds;
	};

	struct Agent_World_Reachables
	{
		Agent_World_Reachables(const State& state, const std::set<World_Id>& designated_worlds)
		{
			std::deque<const World*> frontier;
			for (const World_Id& world_id : designated_worlds)
			{
				frontier.push_back(&state.get_world(world_id));
			}

			while (!frontier.empty())
			{
				const World* world_from = frontier.back();
				frontier.pop_back();
				std::vector<Agent_World_Reachable> reachables;
				for (size_t i = 0; i < state.get_number_of_agents(); ++i)
				{
					Agent_Id agent = { i };
					for (const World& world_to : state.get_worlds())
					{
						if (state.is_one_reachable(agent, world_from, &world_to))
						{
							reachables.push_back({ agent, &world_to });
						}
						if (data.find(&world_to) == data.end() && std::find(frontier.begin(), frontier.end(), &world_to) == frontier.end())
						{
							frontier.push_back(&world_to);
						}
					}
				}
				data.insert({ world_from, std::move(reachables) });
			}
		}

		const std::vector<Agent_World_Reachable>& get(const World* world) const
		{
			return data.at(world);
		}

		// Agent_World_Reachable don't need an ordering as they will be ordered by signature
		std::map<const World*, std::vector<Agent_World_Reachable>> data;
	};

	struct Blocks
	{
		Blocks(const Agent_World_Reachables& agent_world_reachables)
		{
			// Extract signatures
			std::map<std::string, Block> signature_to_block;
			for (const auto& [world, reachables] : agent_world_reachables.data)
			{
				std::string propositions = world->get_true_propositions().to_signature_string();
				signature_to_block[propositions].insert(world);
			}

			// Create blocks, sorted by map
			for (const auto& [propositions, block] : signature_to_block) 
			{
				blocks.push_back(block);
				Block_Id block_index = { blocks.size() - 1 };
				for (const World* world : block.worlds)
				{
					world_to_block.insert({ world, block_index });
				}
			}
		}

		Signature get_signature(const std::vector<Agent_World_Reachable>& world_reachables)
		{
			Signature result;
			for (const Agent_World_Reachable& reachable : world_reachables)
			{
				Block_Id block_index = world_to_block.at(reachable.world);
				result.insert(Agent_Block_Reachable{ reachable.agent, block_index });
			}
			return result;
		}

		void insert_block_and_update(const Block& block) 
		{
			Block_Id new_block_index = { blocks.size() };
			for (const World* world : block.worlds) 
			{
				Block_Id& block_index = world_to_block.at(world);
				blocks.at(block_index.id).remove(world);
				block_index = new_block_index;
			}
			blocks.push_back(block);
		}

		const Block_Id& get_block_id(const World* world) const { return world_to_block.at(world); }
		const Block& get_block(size_t index) const { return blocks.at(index); }
		const Block& get_block(Block_Id index) const { return blocks.at(index.id); }

		size_t size() const { return blocks.size(); }

		std::vector<Block> blocks;
		std::map<const World*, Block_Id> world_to_block;

	};

	State contract(const State& state, const std::set<World_Id>& designated_worlds)
	{
		Agent_World_Reachables agent_world_reachables(state, designated_worlds);
		Blocks blocks(agent_world_reachables);
		size_t old_length = -1;
		size_t new_length = blocks.size();
		while (new_length != old_length)
		{
			for (size_t i = 0; i < new_length; ++i)
			{
				std::map<Signature, Block> new_blocks;
				const Block& block = blocks.get_block(i);
				Signature blockSignature;
				bool first = true;

				// Extract signatures
				for (const World* world : block.worlds)
				{
					const std::vector<Agent_World_Reachable>& world_reachables = agent_world_reachables.get(world);
					Signature signature = blocks.get_signature(world_reachables);
					if (first)
					{
						blockSignature = std::move(signature);
						first = false;
					}
					else if (signature != blockSignature)
					{
						new_blocks[signature].insert(world);
					}
				}

				// Split block
				for (const std::pair<Signature, Block>& kvp : new_blocks)
				{
					const Block& block = kvp.second;
					blocks.insert_block_and_update(block);
				}
			}
			old_length = new_length;
			new_length = blocks.size();
		}

		// Set world propositions

		std::vector<World> worlds;
		for (const Block& block : blocks.blocks)
		{
			worlds.push_back(World(World_Id{ worlds.size() }, block.get_propositions()));
		}

		// Set world relation
		Accessibility_Relations accessibility_relations(worlds.size(), state.get_number_of_agents());

		for (const auto& [world_from, agent_world_reachables_data] : agent_world_reachables.data)
		{
			const Block_Id& block_from = blocks.get_block_id(world_from);
			for (const Agent_World_Reachable& reachable : agent_world_reachables_data)
			{
				const Block_Id& block_to = blocks.get_block_id(reachable.world);
				accessibility_relations.set(reachable.agent, block_from.to_world(), block_to.to_world());
			}
		}

		// Set designated worlds
		std::set<World_Id> new_designated_worlds;
		for (const World_Id& world_id : designated_worlds) 
		{
			const World& world = state.get_world(world_id);
			new_designated_worlds.insert(blocks.get_block_id(&world).to_world());
		}

		return State(worlds, accessibility_relations, new_designated_worlds, state.get_cost());
	}
}