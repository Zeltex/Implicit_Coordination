#pragma once

#include "Formula.hpp"
#include "World.hpp"
#include "Types.hpp"
#include "Misc.hpp"
#include "Agent.hpp"

namespace del {
	class Domain;
	class State {
	public:
		State();
		State(size_t amount_of_agents);

		virtual const Propositions& get_true_propositions(size_t world_id) const;
		virtual std::vector<size_t> get_reachable_worlds(size_t agent_id, size_t world_id) const;

		World&	create_world();
		World&	create_world(const World& world);
		void	create_worlds(size_t amount_to_create);	
		bool	is_one_reachable(Agent_Id agent, World_Id world1, World_Id world2) const;
		bool	is_true(size_t world_id, const Proposition& proposition) const;
		bool	is_world_designated(World_Id world) const;
		void	set_amount_of_agents(size_t amount_of_agents);
		void	set_cost(size_t cost);
		void	set_designated_worlds(const std::vector<World_Id>& worlds);
		void	set_single_designated_world(World_Id world);
		bool	valuate(const Formula& formula, const Domain& domain) const;


		void set_world_designated(World_Id world);
		void add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_true_propositions(World_Id world, const std::vector<Proposition>& propositions);
		void remove_true_propositions(World_Id world, const std::vector<Proposition>& propositions);
		void remove_unreachable_worlds();


		size_t											get_cost() const;
		std::vector<World_Id>							get_designated_world_reachables(Agent_Id agent) const;
		const std::vector<World_Id>&					get_designated_worlds() const;
		size_t											get_designated_worlds_count() const;
		const std::vector<World_Relation>&				get_indistinguishability_relations(Agent_Id agent) const;
		const std::vector<std::vector<World_Relation>>& get_indistinguishability_relations() const;
		size_t											get_number_of_agents() const;
		std::vector<World_Id>							get_reachables(Agent_Id agent, World_Id world) const;
		const World&									get_world(World_Id world) const;
		const std::vector<World>&						get_worlds() const;
		size_t											get_worlds_count() const;


		std::string to_string(const Domain& domain) const;
		std::string to_string(size_t indentation, const Domain& domain) const;
		std::string to_graph(const std::string node_id, const Domain& domain) const;

		bool operator==(const State& other) const;
		size_t to_hash() const;

	private:
		size_t cost;
		size_t number_of_agents;
		std::vector<World> worlds;
		std::vector<World_Id> designated_worlds;
		std::vector<std::vector<World_Relation>> indistinguishability_relation;
	};
}