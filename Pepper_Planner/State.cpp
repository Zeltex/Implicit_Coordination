#include "State.hpp"

namespace del {

	State::State():
		number_of_agents(0), worlds(), designated_worlds(), indistinguishability_relation(){
	}

	State::State(size_t number_of_agents) :
		number_of_agents(0), worlds(), designated_worlds(), indistinguishability_relation() {
		set_amount_of_agents(number_of_agents);
	}

	void State::set_amount_of_agents(size_t number_of_agents) {
		this->number_of_agents = number_of_agents;
		indistinguishability_relation.reserve(number_of_agents);
		perceivability.reserve(number_of_agents);
		observability.reserve(number_of_agents);
		for (size_t i = 0; i < number_of_agents; i++) {
			indistinguishability_relation.emplace_back();
			perceivability.emplace_back();
			observability.emplace_back();
		}
	}

	bool State::valuate(const Formula& formula) const {
		for (auto world : designated_worlds) {
			if (world.id >= worlds.size()) {
				int debug = 0;
			}

			if (!worlds[world.id].valuate(formula)) {
				return false;
			}
		}
		return true;
	}

	const std::vector<World>& State::get_worlds() const {
		return worlds;
	}

	size_t State::get_number_of_agents() const{
		return number_of_agents;
	}

	bool State::is_one_reachable(Agent_Id agent, World_Id world1, World_Id world2) const {
		for (auto relations : indistinguishability_relation[agent.id]) {
			if (relations.world_from == world1 && relations.world_to == world2) {
				return true;
			}
		}
		return false;
	}


	std::vector<World_Id> State::get_designated_world_reachables(Agent_Id agent) const {
		std::vector<World_Id> frontier;
		std::vector<World_Id> visited;
		for (auto designated_world : designated_worlds) {
			frontier.push_back(designated_world);
			visited.push_back(designated_world);
		}
		while (!frontier.empty()) {
			auto current = frontier.back();
			frontier.pop_back();
			for (auto relation : indistinguishability_relation[agent.id]) {
				if (relation.world_from.id == current.id && 
					std::find(visited.begin(), visited.end(), relation.world_to) == visited.end()) {

					frontier.push_back(relation.world_to);
					visited.push_back(relation.world_to);
				}
			}
		}
		return visited;
	}

	void State::add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to) {
		indistinguishability_relation[agent.id].emplace_back(world_from, world_to);
	}

	void State::add_true_propositions(World_Id world, std::vector<Proposition_Instance> propositions) {
		worlds[world.id].add_true_propositions(propositions);
	}

	void State::remove_true_propositions(World_Id world, std::vector<Proposition_Instance> propositions) {
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

	void State::add_designated_world(World_Id world) {
		if (find(designated_worlds.begin(), designated_worlds.end(), world) != designated_worlds.end()) {
			return;
		}
		designated_worlds.push_back(world);
	}

	void State::copy_perceivability_and_observability(const State& other) {
		perceivability = other.perceivability;
		observability = other.observability;
	}

	size_t State::get_worlds_count() const {
		return worlds.size();
	}

	size_t State::get_designated_worlds_count() const {
		return designated_worlds.size();
	}

	const std::vector<World_Relation>& State::get_indistinguishability_relations(Agent_Id agent) const {
		return indistinguishability_relation[agent.id];
	}

	const std::vector<World_Id>& State::get_designated_worlds() const {
		return designated_worlds;
	}

	const World& State::get_world(World_Id world) const {
		return worlds[world.id];
	}

	void State::set_single_designated_world(World_Id world) {
		designated_worlds.clear();
		designated_worlds.push_back(world);
	}

	void State::add_observability(Agent_Id observer, std::vector<Agent_Id> agents) {
		for (auto agent : agents) {
			auto& temp = observability[observer.id];
			if (find(temp.begin(), temp.end(), agent) == temp.end()) {
				observability[observer.id].push_back(agent);
			}
		}
	}

	void State::add_perceivability(Agent_Id perceiver, std::vector<Agent_Id> agents) {
		for (auto agent : agents) {
			auto& temp = perceivability[perceiver.id];
			if (find(temp.begin(), temp.end(), agent) == temp.end()) {
				perceivability[perceiver.id].push_back(agent);
			}
		}
	}

	void State::remove_perceivability(Agent_Id perceiver, std::vector<Agent_Id> agents) {
		for (auto agent : agents) {
			auto& temp = perceivability[perceiver.id];
			auto it = find(temp.begin(), temp.end(), agent);
			if (it != temp.end()) {
				temp.erase(it);
			}
		}
	}

	void State::remove_observability(Agent_Id observer, std::vector<Agent_Id> agents) {
		for (auto agent : agents) {
			auto& temp = observability[observer.id];
			auto it = find(temp.begin(), temp.end(), agent);
			if (it != temp.end()) {
				temp.erase(it);
			}
		}
	}

	const std::vector<Agent_Id>& State::get_observables(Agent_Id agent) const {
		return observability[agent.id];
	}

	const std::vector<Agent_Id>& State::get_perceivables(Agent_Id agent) const {
		return perceivability[agent.id];
	}

	std::string State::to_string() const {
		return to_string(3);
	}

	void State::set_designated_worlds(std::vector<World_Id> worlds) {
		designated_worlds = worlds;
	}

	void State::remove_unreachable_worlds() {

		// Convert relations
		std::unordered_map<size_t, std::unordered_set<size_t>> relations;
		for (auto& world : worlds) {
			relations[world.get_id().id].reserve(worlds.size());
		}
		for (auto& agent_relations : indistinguishability_relation) {
			for (const auto& relation : agent_relations) {
				relations[relation.world_from.id].insert(relation.world_to.id);
			}
		}

		// Get reachable worlds
		std::vector<size_t> frontier;
		std::unordered_set<size_t> visited;
		for (auto designated_world : designated_worlds) {
			frontier.push_back(designated_world.id);
			visited.insert(designated_world.id);
		}
		while (!frontier.empty()) {
			const auto& current = frontier.back();
			frontier.pop_back();
			for (const auto& relation : relations[current]) {
				if (std::find(visited.begin(), visited.end(), relation) == visited.end()) {
					frontier.push_back(relation);
					visited.insert(relation);
				}
			}
		}
		std::unordered_map<size_t, size_t> world_old_to_new;
		world_old_to_new.reserve(worlds.size());

		// Delete worlds
		std::vector<World> new_worlds;
		new_worlds.reserve(visited.size());
		{
			size_t counter = 0;
			for (auto& world : worlds) {
				if (visited.find(world.get_id().id) != visited.end()) {
					world_old_to_new[world.get_id().id] = counter;
					world.set_id({ counter });
					new_worlds.emplace_back(std::move(world));
					counter++;
				}
			}
			worlds = std::move(new_worlds);
		}

		// Delete relations
		std::vector<std::vector<World_Relation>> new_relations;
		new_relations.reserve(number_of_agents);
		for (size_t i = 0; i < number_of_agents; i++) {
			new_relations.emplace_back();
			new_relations[i].reserve(worlds.size());
		}
		size_t agent = 0;
		for (auto& agent_relations : indistinguishability_relation) {
			for (const auto& relation : agent_relations) {
				if (visited.find(relation.world_from.id) != visited.end() 
					&& visited.find(relation.world_to.id) != visited.end()) {
					new_relations[agent].emplace_back(
						World_Id{ world_old_to_new[relation.world_from.id] },
						World_Id{ world_old_to_new[relation.world_to.id] });
				}
			}
			agent++;
		}
		indistinguishability_relation = std::move(new_relations);

		std::vector<World_Id> new_designated_worlds;
		new_designated_worlds.reserve(designated_worlds.size());
		for (auto& world : designated_worlds) {
			new_designated_worlds.push_back({ world_old_to_new[world.id] });
		}
		designated_worlds = std::move(new_designated_worlds);
	}


	std::string State::to_string(size_t indentation) const {

		size_t relations_size = 0;
		for (auto relation : indistinguishability_relation) {
			relations_size += relation.size();
		}

		std::string result = get_indentation(indentation) + " State\n" + get_indentation(indentation - 1) + " Sizes: (agents, " + std::to_string(number_of_agents) +
			") (worlds, " + std::to_string(worlds.size()) +
			") (designated worlds, " + std::to_string(designated_worlds.size()) +
			") (relations, " + std::to_string(relations_size) + ")\n";
		result += get_indentation(indentation - 1) + " Designated worlds: ";
		bool first = true;
		for (auto designated_world : designated_worlds) {
			if (first) {
				first = false;
			} else {
				result += ", ";
			}
			result += std::to_string(designated_world.id);
		}
		result += "\n" + get_indentation(indentation - 1) + " ({Agent}, {World from}, {World to}) Relations";
		int current_agent = 0;
		for (auto agent_relations : indistinguishability_relation) {
			for (auto relation : agent_relations) {
				result += "\n(" 
					+ std::to_string(current_agent) + ", "
					+ std::to_string(relation.world_from.id) + ", "
					+ std::to_string(relation.world_to.id) + ")";
			}
			current_agent++;
		}
		result += "\n" + get_indentation(indentation - 1) + " World {id}: {propositions}";
		for (auto world : worlds) {
			result += "\n" + world.to_string();
		}
		return result;
	}

	std::string State::to_graph(const std::vector<Agent>& agents, const std::string node_id) const {
		std::string result;
		for (auto& world : worlds) {
			std::string propositions;
			bool first = true;
			for (auto proposition : world.get_true_propositions()) {
				if (first) {
					first = false;
				} else {
					propositions += ", ";
				}
				propositions += proposition.to_string();
			}
			result += node_id + std::to_string(world.get_id().id) + " [label=\"" + std::to_string(world.get_id().id) + "\n" + propositions + "\"";
			if (std::find(designated_worlds.begin(), designated_worlds.end(), world.get_id()) != designated_worlds.end()) {
				result += ", shape=doublecircle];\n";
			} else {
				result += "];\n";
			}
		}
		size_t agent_id = 0;
		for (auto& agent_relations : indistinguishability_relation) {
			for (auto& relation : agent_relations) {
				result += node_id
					+ std::to_string(relation.world_from.id) 
					+ " -> " 
					+ node_id
					+ std::to_string(relation.world_to.id) 
					+ "[label=\"" 
					+ agents[agent_id].get_name()
					+ "\"];\n";
			}
			agent_id++;
		}
		return result;
	}
}