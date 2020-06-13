#include "State.hpp"

namespace del {

	State::State(size_t number_of_agents):
		number_of_agents(number_of_agents), worlds(), designated_worlds(), indistinguishability_relation(){
		
		indistinguishability_relation.reserve(number_of_agents);
		for (size_t i = 0; i < number_of_agents; i++) {
			indistinguishability_relation.emplace_back();
		}
	}


	bool State::valuate(Formula& formula) {
		for (auto world : designated_worlds) {
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

	bool State::is_one_reachable(World_Id world1, World_Id world2, Agent_Id agent) {
		for (auto relations : indistinguishability_relation[agent.id]) {
			if (relations.world_from == world1 && relations.world_to == world2) {
				return true;
			}
		}
		return false;
	}

	void State::add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to) {
		indistinguishability_relation[agent.id].emplace_back(world_from, world_to);
	}

	void State::add_true_propositions(World_Id world, std::unordered_set<std::string> propositions) {
		worlds[world.id].add_true_propositions(propositions);
	}

	void State::remove_true_propositions(World_Id world, std::unordered_set<std::string> propositions) {
		worlds[world.id].remove_true_propositions(propositions);
	}

	World& State::create_world() {
		World_Id new_world = World_Id{ worlds.size() };
		worlds.emplace_back(new_world);
		return worlds[new_world.id];
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
}