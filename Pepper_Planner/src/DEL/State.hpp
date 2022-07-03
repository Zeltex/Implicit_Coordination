#pragma once

#include <set>
#include <vector>
#include <optional>

#include "Formula.hpp"
#include "World.hpp"
#include "Types.hpp"
#include "Misc.hpp"
#include "Accessibility_Relation.hpp"

namespace del {

	class Action;
	class Agents;
	class Domain;
	class General_State;
	class State {
	public:
		State();
		State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost);
		State(const State& other, World_Id designated_world);
		State(const General_State& other, const Propositions_Lookup& propositions_lookup, const Agents& agents);

		virtual const Propositions& get_true_propositions(World_Id world_id) const;
		virtual std::set<size_t> get_reachable_worlds(Agent_Id agent_id, World_Id world_id) const;



		std::vector<State>			get_all_perspective_shifts(size_t number_of_agents) const;
		size_t						get_cost() const;
		const std::set<World_Id>&	get_designated_worlds() const;
		size_t						get_designated_worlds_count() const;
		size_t						get_number_of_agents() const;
		const World&				get_world(World_Id world) const;
		const std::vector<World>&	get_worlds() const;
		size_t						get_worlds_count() const;
		std::optional<State>		product_update(const Action* action, const Domain& domain) const;

		State				contract() const;
		bool				is_bisimilar_to(const State& other) const;
		bool				is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const;
		bool				is_true(const World_Id& world_id, const Proposition& proposition) const;
		bool				is_world_designated(World_Id world) const;
		void				shift_perspective(Agent_Id agent, bool is_exclusive=false);
		std::vector<State>	split_into_globals() const;
		void				remove_unreachable_worlds();
		bool				valuate(const Formula& formula, const Domain& domain) const;

		bool operator==(const State& other) const;
		size_t to_hash() const;
		std::string to_string(const Domain& domain) const;
		std::string to_string(size_t indentation, const Domain& domain) const;

	private:

		size_t cost;
		std::vector<World> worlds;
		std::set<World_Id> designated_worlds;
		Accessibility_Relations accessibility_relations;
	};
}