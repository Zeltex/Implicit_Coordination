#include "State.hpp"
#include "Domain.hpp"
#include "Formula_Input_Impl.hpp"
#include "Action.hpp"

namespace del {

	State::State(size_t number_of_agents, size_t world_count) :
		cost(0), worlds(), designated_worlds(), accessibility_relations(world_count, number_of_agents) {
	}

	State::State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost)
		: cost(cost), worlds(worlds), designated_worlds(designated_worlds), accessibility_relations(accessbility_relations)
	{

	}
	std::vector<State> State::get_all_perspective_shifts(size_t number_of_agents) const
	{
		std::vector<State> perspective_shifts;
		perspective_shifts.reserve(number_of_agents);

		for (size_t i = 0; i < number_of_agents; ++i)
		{
			State temp_state = *this;
			temp_state.shift_perspective(Agent_Id{ i });
			perspective_shifts.push_back(temp_state);
		}
	}

	void State::shift_perspective(Agent_Id agent, bool is_exclusive) 
	{
		std::set<World_Id> designated_copy;
		while (designated_copy.size() != designated_worlds.size())
		{
			designated_copy = designated_worlds;
			for (const World_Id& designated : designated_copy) {
				if (is_exclusive) 
				{
					designated_worlds.erase(designated);
				}

				for (const World& world : worlds) {
					if (accessibility_relations.has_direct_relation(agent, designated, world.get_id()))
					{
						designated_worlds.insert(world.get_id());
					}
				}
			}
		}

		// TODO - Might make this optional for optimisation
		remove_unreachable_worlds();
	}

	bool State::is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const
	{
		return accessibility_relations.has_direct_relation(agent, world_from, world_to);
	}


	const Propositions& State::get_true_propositions(size_t world_id) const {
		return worlds[world_id].get_true_propositions();
	}

	bool State::is_true(size_t world_id, const Proposition& proposition) const {
		return worlds[world_id].get_true_propositions().contains(proposition);
	}

	std::vector<size_t> State::get_reachable_worlds(size_t agent_id, size_t world_id) const {
		std::vector<size_t> frontier = { { world_id } };
		std::vector<size_t> visited;
		while (!frontier.empty()) {
			auto current = frontier.back();
			frontier.pop_back();
			for (const auto& relation : indistinguishability_relation[agent_id]) {
				if (relation.world_from.id == current &&
					std::find(visited.begin(), visited.end(), relation.world_to.id) == visited.end()) {

					frontier.push_back(relation.world_to.id);
					visited.push_back(relation.world_to.id);
				}
			}
		}
		return std::move(visited);
	}

	bool State::valuate(const Formula& formula, const Domain& domain) const {
		Formula_Input_Impl input = { this, &domain };
		for (const auto& world : designated_worlds) {
			if (!formula.valuate(world.id, &input)) {
				return false;
			}
		}
		return true;
	}

	const std::vector<World>& State::get_worlds() const {
		return worlds;
	}

	void State::add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to) {
		indistinguishability_relation[agent.id].emplace_back(world_from, world_to);
	}

	void State::add_true_propositions(World_Id world, const std::vector<Proposition>& propositions) {
		worlds[world.id].add_true_propositions(propositions);
	}

	void State::remove_true_propositions(World_Id world, const std::vector<Proposition>& propositions) {
		worlds[world.id].remove_true_propositions(propositions);
	}

	World& State::create_world() {
		World_Id new_world = World_Id{ worlds.size() };
		worlds.emplace_back(new_world);
		return worlds[new_world.id];
	}

	World& State::create_world(const World& world) {
		World_Id new_world = World_Id{ worlds.size() };
		worlds.emplace_back(new_world, world.get_true_propositions());
		return worlds[new_world.id];
	}

	void State::create_worlds(size_t amount_to_create) {
		for (size_t i = 0; i < amount_to_create; i++) {
			World_Id new_world = World_Id{ worlds.size() };
			worlds.emplace_back(new_world);
		}
	}

	bool State::is_world_designated(World_Id world) const {
		return find(designated_worlds.begin(), designated_worlds.end(), world) != designated_worlds.end();
	}

	void State::set_world_designated(World_Id world) {
		designated_worlds.insert(world);
	}

	size_t State::get_worlds_count() const {
		return worlds.size();
	}

	size_t State::get_designated_worlds_count() const {
		return designated_worlds.size();
	}

	const std::set<World_Id>& State::get_designated_worlds() const {
		return designated_worlds;
	}

	const World& State::get_world(World_Id world) const {
		return worlds[world.id];
	}

	size_t State::get_cost() const {
		return cost;
	}

	void State::set_cost(size_t cost) {
		this->cost = cost;
	}

	void State::set_single_designated_world(World_Id world) {
		designated_worlds.clear();
		designated_worlds.insert(world);
	}

	void State::set_designated_worlds(const std::set<World_Id>& worlds) {
		designated_worlds = worlds;
	}

	void State::remove_unreachable_worlds() {
		std::set<World_Id> unreachable_worlds = accessibility_relations.get_unreachable_worlds(designated_worlds);
		std::map<World_Id, World_Id> world_old_to_new;
		std::vector<World> new_worlds;
		new_worlds.reserve(unreachable_worlds.size());

		for (const World& old_world : worlds)
		{
			if (unreachable_worlds.find(old_world.get_id()) == unreachable_worlds.end()) 
			{
				World_Id new_world_id{ new_worlds.size() };
				world_old_to_new.insert({ old_world.get_id(), new_world_id });
				World new_world(old_world);
				new_world.set_id(new_world_id);
				new_worlds.push_back(new_world);
			}
		}
		worlds = new_worlds;
		accessibility_relations.convert_world_ids(world_old_to_new);

		std::set<World_Id> new_designated_worlds;
		for (auto& world : designated_worlds) 
		{
			new_designated_worlds.insert(world_old_to_new.at(world));
		}
		designated_worlds = new_designated_worlds;
	}


	std::optional<State> State::product_update(const Action& action, const Domain& domain) const
	{
		World_Id new_world_id{ 0 };
		Formula_Input_Impl input = { this, &domain };
		std::vector<World> new_worlds;
		std::set<World_Id> new_designated_worlds;
		std::vector<World_Entry> world_conversion;
		std::set<World_Id> unassigned_designated_worlds = designated_worlds;

		for (const World& world : worlds) {
			for (const Action_Event& event : action.get_events()) {
				
				if (!event.get_preconditions().valuate(world.get_id().id, &input)) 
				{
					continue;
				}

				// Create world
				new_worlds.push_back(World(world, event, new_world_id));

				// Set designated
				if (is_world_designated(world.get_id()) && action.is_event_designated(event.get_id())) 
				{
					new_designated_worlds.insert(new_world_id);
					unassigned_designated_worlds.erase(world.get_id());
				}

				world_conversion.push_back({ world.get_id(), event.get_id(), new_world_id });
				++new_world_id;
			}
		}

		// Some designated world did not have associated designated event
		if (!unassigned_designated_worlds.empty())
		{
			return {};
		}


		// Update accessbility relations
		Accessibility_Relations new_accessbility_relations = accessibility_relations.product_update(world_conversion, action, domain, *this);

		if (!new_accessbility_relations.is_serial_transitive_euclidean())
		{
			return {};
		}
		else
		{
			State result(new_worlds, new_accessbility_relations, new_designated_worlds, cost + action.get_cost());
			result.remove_unreachable_worlds();

			return result;
		}
	}

	std::vector<State> State::split_into_globals() const
	{
		std::vector<State> result;
		for (const World_Id& designated_world : designated_worlds) {
			State new_state = State(*this);
			new_state.set_single_designated_world(designated_world);
			new_state.remove_unreachable_worlds();
			result.push_back(std::move(new_state));
		}
		return result;
	}

	bool State::operator==(const State& other) const {
		if (cost != other.cost || worlds.size() != other.worlds.size() || designated_worlds.size() != other.designated_worlds.size())
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

	size_t State::to_hash() const {
		std::vector<std::string> hashes;
		size_t relations_size = 0;
		std::string relations_string = accessibility_relations.to_hashable_string(relations_size);

		hashes.reserve(worlds.size() + designated_worlds.size() + relations_size);

		hashes.push_back(std::to_string(worlds.size()));
		hashes.push_back(std::to_string(designated_worlds.size()));
		hashes.push_back(std::to_string(relations_size));

		for (auto& world : worlds) {
			hashes.emplace_back(std::move(world.to_hash()));
		}
		for (auto& designated_world : designated_worlds) {
			hashes.emplace_back(std::to_string(designated_world.id));
		}
		std::string hash = relations_string;
		hash.reserve(hashes.size() * sizeof(size_t));
		for (const auto& entry : hashes) hash += entry;

		return std::hash<std::string>()(hash);
	}

	std::string State::to_string(const Domain& domain) const {
		return to_string(3, domain);
	}


	std::string State::to_string(size_t indentation, const Domain& domain) const {
		std::string result = get_indentation(indentation) + " State\n" + get_indentation(indentation - 1) + " Sizes: " +
			") (worlds, " + std::to_string(worlds.size()) +
			") (designated worlds, " + std::to_string(designated_worlds.size()) +
			") (cost, " + std::to_string(cost) + ")\n";
		result += get_indentation(indentation - 1) + " Designated worlds: ";
		bool first = true;
		for (const auto& designated_world : designated_worlds) {
			if (first) {
				first = false;
			} else {
				result += ", ";
			}
			result += std::to_string(designated_world.id);
		}
		result += "\n" + get_indentation(indentation - 1) + " ({Agent}, {World from}, {World to}) Relations";
		result += "\n" + accessibility_relations.to_string(domain);
		result += "\n" + get_indentation(indentation - 1) + " World {id}: {propositions}";
		for (const auto& world : worlds) {
			result += "\n" + world.to_string(domain);
		}
		return result;
	}

	State State::contract() const
	{
		return perform_bisimilar_contraction(*this);
	}
}