#pragma once

#include <set>
#include <vector>

#include "Formula.hpp"
#include "World.hpp"
#include "Types.hpp"
#include "Misc.hpp"
#include "Agent.hpp"
#include "Accessibility_Relation.hpp"

namespace del {

	class Action;
	class Domain;
	class State {
	public:
		State();
		State(size_t amount_of_agents);
		State(size_t number_of_agents, size_t world_count);
		State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost);

		virtual const Propositions& get_true_propositions(size_t world_id) const;
		virtual std::vector<size_t> get_reachable_worlds(size_t agent_id, size_t world_id) const;

		World&	create_world();
		World&	create_world(const World& world);
		void	create_worlds(size_t amount_to_create);	
		bool	is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const;
		bool	is_true(size_t world_id, const Proposition& proposition) const;
		bool	is_world_designated(World_Id world) const;
		void	set_cost(size_t cost);
		void	set_designated_worlds(const std::set<World_Id>& worlds);
		void	set_single_designated_world(World_Id world);
		void	shift_perspective(Agent_Id agent, bool is_exclusive=false);
		bool	valuate(const Formula& formula, const Domain& domain) const;


		void set_world_designated(World_Id world);
		void add_indistinguishability_relation(Agent_Id agent, World_Id world_from, World_Id world_to);
		void add_true_propositions(World_Id world, const std::vector<Proposition>& propositions);
		void remove_true_propositions(World_Id world, const std::vector<Proposition>& propositions);
		void remove_unreachable_worlds();

		State											contract() const;
		std::vector<State>								get_all_perspective_shifts(size_t number_of_agents) const;
		size_t											get_cost() const;
		const std::set<World_Id>&						get_designated_worlds() const;
		size_t											get_designated_worlds_count() const;
		size_t											get_number_of_agents() const;
		const World&									get_world(World_Id world) const;
		const std::vector<World>&						get_worlds() const;
		size_t											get_worlds_count() const;
		std::optional<State>							product_update(const Action& action, const Domain& domain) const;
		std::vector<State>								split_into_globals() const;



		std::string to_string(const Domain& domain) const;
		std::string to_string(size_t indentation, const Domain& domain) const;

		bool operator==(const State& other) const;
		size_t to_hash() const;

	private:

		std::vector<World_Id> get_unreachable_worlds() const;

		size_t cost;
		std::vector<World> worlds;
		std::set<World_Id> designated_worlds;
		Accessibility_Relations accessibility_relations;
	};
}