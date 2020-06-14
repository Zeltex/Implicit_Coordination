#pragma once

#include "Formula.hpp"
#include "World.hpp"
#include "Types.hpp"

namespace del {

	class State {
	public:
		State() = delete;
		State(size_t number_of_agents);
		bool valuate(Formula& formula);
		bool is_world_designated(World_Id world) const;
		void add_designated_world(World_Id world);
		const std::vector<World>& get_worlds() const;
		size_t get_number_of_agents() const;
		bool is_one_reachable(Agent_Id agent, World_Id world1, World_Id world2);
		void add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_true_propositions(World_Id world, std::unordered_set<std::string> propositions);
		void remove_true_propositions(World_Id world, std::unordered_set<std::string> propositions);
		World& create_world();

	private:
		size_t number_of_agents;
		std::vector<World> worlds;
		std::vector<World_Id> designated_worlds;
		std::vector<std::vector<World_Relation>> indistinguishability_relation;
	};
}