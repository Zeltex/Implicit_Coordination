#pragma once

#include "Formula.hpp"
#include "World.hpp"
#include "Types.hpp"

namespace del {

	class State {
	public:
		State() = delete;
		State(size_t number_of_agents);
		bool valuate(const Formula& formula) const;
		bool is_world_designated(World_Id world) const;
		bool is_one_reachable(Agent_Id agent, World_Id world1, World_Id world2);
		
		void add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_true_propositions(World_Id world, std::unordered_set<std::string> propositions);
		void add_designated_world(World_Id world);
		void remove_true_propositions(World_Id world, std::unordered_set<std::string> propositions);
		void set_global_for_agent(Agent_Id agent, World_Id world);

		World& create_world();
		World& create_world(const World& world);
		std::vector<World_Id> get_designated_world_reachables(Agent_Id agent);
		const std::vector<World>& get_worlds() const;

		size_t get_number_of_agents() const;
		size_t get_worlds_count() const;
		size_t get_designated_worlds_count() const;

		const std::vector<World_Relation>& get_indistinguishability_relations(Agent_Id agent) const;
		const std::vector<World_Id>& get_designated_worlds() const;
		const World& get_world(World_Id world) const;

		std::string to_string() const;

	private:
		size_t number_of_agents;
		std::vector<World> worlds;
		std::vector<World_Id> designated_worlds;
		std::vector<std::vector<World_Relation>> indistinguishability_relation;
	};
}