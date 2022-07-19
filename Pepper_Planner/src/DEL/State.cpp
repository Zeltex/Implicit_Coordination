#include "State.hpp"

#include "Action.hpp"
#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Bisimulation_Context.hpp"
#include "Domain.hpp"
#include "General_State.hpp"
#include "Types.hpp"

namespace del
{


	State::State(const General_State& other, const Propositions_Lookup& propositions_lookup, const Agents& agents, const Atom_Lookup& atom_lookup)
		: cost(other.cost),
		designated_worlds(other.designated_worlds),
		accessibility_relations(other.worlds.size(), &agents)
	{
		Converter_Problem converter(&propositions_lookup, &atom_lookup, &agents);
		for (const General_World& general_world : other.worlds)
		{
			worlds.emplace_back(general_world, &converter);
		}

		for (const Agent_World_Relation& relation : other.agent_world_relations)
		{
			accessibility_relations.set(relation.agent, relation.world_from, relation.world_to);
		}
	}

	State::State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost)
		: cost(cost), worlds(worlds), designated_worlds(designated_worlds), accessibility_relations(accessbility_relations)
	{

	}

	State::State(std::vector<World>&& worlds, Accessibility_Relations&& accessbility_relations, std::set<World_Id>&& designated_worlds, size_t cost)
		: cost(cost), worlds(std::move(worlds)), designated_worlds(std::move(designated_worlds)), accessibility_relations(std::move(accessbility_relations))
	{

	}

	State::State(const State& other, World_Id designated_world)
		: cost(other.cost), worlds(other.worlds), accessibility_relations(other.accessibility_relations)
	{
		this->designated_worlds.insert(designated_world);
	}

	State State::shift_and_contract(const Agent* agent) const
	{
		auto worlds = get_reachable_worlds(agent);
		return contract(worlds);
	}

	bool State::is_one_reachable(Agent_Id agent, const World* world_from, const World* world_to) const
	{
		return accessibility_relations.has_direct_relation(agent, world_from->get_id(), world_to->get_id());
	}

	bool State::is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const
	{
		return accessibility_relations.has_direct_relation(agent, world_from, world_to);
	}

	bool State::is_valid() const
	{
		return accessibility_relations.is_serial_transitive_euclidean();
	}

	std::set<World_Id> State::get_reachable_worlds(const Agent* agent) const
	{
		std::set<World_Id> result;
		for (auto designated_world : designated_worlds)
		{
			for (auto& world : worlds)
			{
				if (is_one_reachable(agent->get_id(), designated_world, world.get_id()))
				{
					result.insert(world.get_id());
				}
			}
		}
		return result;
	}

	std::set<World_Id> State::get_reachable_worlds(const Agent* agent, World_Id world_id) const
	{
		// Due to the serial, transitive and euclidean conditions we only need to check depth one
		std::set<World_Id> result;
		Agent_Id agent_id = agent->get_id();
		for (const World& world : worlds)
		{
			if (accessibility_relations.has_direct_relation(agent_id, world_id, world.get_id()))
			{
				result.insert(world.get_id());
			}
		}
		return result;
	}

	bool State::valuate(const Formula& formula, const Domain& domain) const
	{
		for (const auto& world : designated_worlds)
		{
			if (!formula.valuate(&get_world(world), domain, *this))
			{
				return false;
			}
		}
		return true;
	}

	bool State::valuate(const Formula& formula, const Domain& domain, const World* designated_world) const
	{
		return formula.valuate(designated_world, domain, *this);
	}

	const std::vector<World>& State::get_worlds() const
	{
		return worlds;
	}

	const std::set<World_Id>& State::get_designated_worlds() const
	{
		return designated_worlds;
	}

	const World& State::get_world(World_Id world) const
	{
		return worlds[world.id];
	}

	size_t State::get_cost() const
	{
		return cost;
	}

	std::optional<State> State::product_update(const Action* action, const Domain& domain) const
	{
		return product_update(action, domain, designated_worlds);
	}

	std::optional<State> State::product_update(const Action* action, const Domain& domain, const std::set<World_Id>& designated_worlds) const
	{
		World_Id new_world_id{ 0 };
		std::vector<World> new_worlds;
		std::vector<World_Entry> world_conversion;

		// Must reserve enough memory to not invalidate World_Entry pointers
		new_worlds.reserve(worlds.size() * action->get_events().size());
		world_conversion.reserve(worlds.size() * 2);

		std::set<World_Id> new_designated_worlds;
		std::vector<bool> unassigned_designated_worlds(worlds.size(), false);

		for (auto& designated_world : designated_worlds)
		{
			unassigned_designated_worlds.at(designated_world.id) = true;
		}

		for (const World& world : worlds)
		{
			for (const Action_Event& action_event : action->get_events())
			{

				if (!action_event.get_preconditions().valuate(&world, domain, *this))
				{
					continue;
				}

				// Create world
				new_worlds.emplace_back(world, action_event, new_world_id);

				bool is_world_designated = designated_worlds.find(world.get_id()) != designated_worlds.end();

				// Set designated
				if (is_world_designated && action_event.is_designated())
				{
					new_designated_worlds.insert(new_world_id);
					unassigned_designated_worlds.at(world.get_id().id) = false;
				}

				world_conversion.emplace_back(&world, action_event.get_id(), &new_worlds.back());
				++new_world_id;
			}
		}

		// Some designated world did not have associated designated event
		if (std::find(unassigned_designated_worlds.begin(), unassigned_designated_worlds.end(), true) != unassigned_designated_worlds.end())
		{
			return {};
		}


		// Update accessbility relations
		Accessibility_Relations new_accessbility_relations = accessibility_relations.product_update(world_conversion, action, domain, *this, new_world_id.id);

		if (!new_accessbility_relations.is_serial_transitive_euclidean())
		{
			return {};
		}
		else
		{
			State result(new_worlds, new_accessbility_relations, new_designated_worlds, cost + action->get_cost());
			return result;
		}
	}

	std::vector<State> State::split_into_globals() const
	{
		std::vector<State> result;
		result.reserve(designated_worlds.size());
		for (const World_Id& designated_world : designated_worlds)
		{
			result.emplace_back(std::move(contract({ designated_world })));
		}
		return result;
	}

	bool State::operator==(const State& other) const
	{
		if (worlds.size() != other.worlds.size() || designated_worlds.size() != other.designated_worlds.size())
		{
			return false;
		}

		for (size_t i = 0; i < worlds.size(); i++)
		{
			if (worlds[i] != other.worlds[i])
			{
				return false;
			}
		}

		auto it1 = designated_worlds.begin();
		auto it2 = other.designated_worlds.begin();

		for (; it1 != designated_worlds.end(); ++it1, ++it2)
		{
			if (*it1 != *it2)
			{
				return false;
			}
		}

		if (accessibility_relations != other.accessibility_relations)
		{
			return false;
		}

		return true;
	}
	size_t State::to_hash() const
	{
		return to_hash(designated_worlds);
	}

	size_t State::to_hash(const std::set<World_Id>& designated_worlds) const
	{
		std::vector<std::string> hashes;
		size_t relations_size = 0;
		std::string relations_string = accessibility_relations.to_hashable_string(relations_size);

		hashes.reserve(worlds.size() + designated_worlds.size() + relations_size);

		hashes.push_back(std::to_string(worlds.size()));
		hashes.push_back(std::to_string(designated_worlds.size()));
		hashes.push_back(std::to_string(relations_size));

		for (auto& world : worlds)
		{
			hashes.emplace_back(std::move(world.to_hash()));
		}
		for (auto& designated_world : designated_worlds)
		{
			hashes.emplace_back(std::to_string(designated_world.id));
		}
		std::string hash = relations_string;
		hash.reserve(hashes.size() * sizeof(size_t));
		for (const auto& entry : hashes) hash += entry;

		return std::hash<std::string>()(hash);
	}

	//size_t State::to_hash(const std::set<World_Id>& designated_worlds) const
	//{
	//	std::string hash;
	//	hash.reserve(accessibility_relations.get_agents()->size() * worlds.size() * worlds.size() * sizeof(size_t));
	//	size_t relations_size = 0;
	//	hash += accessibility_relations.to_hashable_string(relations_size);

	//	//hashes.reserve(worlds.size() + designated_worlds.size() + relations_size);

	//	hash += std::to_string(worlds.size());
	//	hash += std::to_string(designated_worlds.size());
	//	hash += std::to_string(relations_size);

	//	for (auto& world : worlds)
	//	{
	//		hash += world.to_hash();
	//	}
	//	for (auto& designated_world : designated_worlds)
	//	{
	//		hash += std::to_string(designated_world.id);
	//	}
	//	return std::hash<std::string>()(hash);
	//}


	std::string State::to_string() const
	{
		return to_string(3);
	}


	std::string State::to_string(size_t indentation) const
	{
		std::string indent_n(indentation, '-');
		std::string indent_n1(indentation - 1, '-');
		std::string result = indent_n + " State\n" + indent_n1 + " Sizes: " +
			") (worlds, " + std::to_string(worlds.size()) +
			") (designated worlds, " + std::to_string(designated_worlds.size()) +
			") (cost, " + std::to_string(cost) + ")\n";
		result += indent_n1 + " Designated worlds: ";
		bool first = true;
		for (const auto& designated_world : designated_worlds)
		{
			if (first)
			{
				first = false;
			}
			else
			{
				result += ", ";
			}
			result += std::to_string(designated_world.id);
		}
		result += "\n" + indent_n1 + " ({Agent}, {World from}, {World to}) Relations";
		result += "\n" + accessibility_relations.to_string();
		result += "\n" + indent_n1 + " World {id}: {propositions}";
		for (const auto& world : worlds)
		{
			result += "\n" + world.to_string();
		}
		return result;
	}

	State State::contract(const std::set<World_Id>& designated_worlds) const
	{
		return bisimulation_context::contract(*this, designated_worlds);
	}

	State State::contract() const
	{
		return bisimulation_context::contract(*this, designated_worlds);
	}

	const Agents* State::get_agents() const
	{
		return accessibility_relations.get_agents();
	}
}