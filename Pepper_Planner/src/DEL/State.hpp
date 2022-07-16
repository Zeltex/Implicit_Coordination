#pragma once

#include "Accessibility_Relation.hpp"
#include "Formula.hpp"
#include "Misc.hpp"
#include "Proposition_Instance.hpp"
#include "Types.hpp"
#include "World.hpp"

#include <set>
#include <vector>
#include <optional>

namespace del {

	class Action;
	class Agent;
	class Agents;
	class Atom_Lookup;
	class Domain;
	class General_State;
	class State {
	public:
		State();
		State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost);
		State(const State& other, World_Id designated_world);
		State(const General_State& other, const Propositions_Lookup& propositions_lookup, const Agents& agents, const Atom_Lookup& atom_lookup);

		virtual const Propositions& get_true_propositions(World_Id world_id) const;
		virtual std::set<World_Id> get_reachable_worlds(const Agent* agent, World_Id world_id) const;

		size_t						get_cost() const;
		const std::set<World_Id>&	get_designated_worlds() const;
		size_t						get_designated_worlds_count() const;
		size_t						get_number_of_agents() const;
		const World&				get_world(World_Id world) const;
		const std::vector<World>&	get_worlds() const;
		size_t						get_worlds_count() const;
		std::optional<State>		product_update(const Action* action, const Domain& domain) const;
		std::optional<State>		product_update(const Action* action, const Domain& domain, const std::set<World_Id>& designated_worlds) const;

		State				contract(const std::set<World_Id>& designated_worlds) const;
		State				contract() const;
		bool				is_bisimilar_to(const State& other) const;
		bool				is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const;
		bool				is_one_reachable(Agent_Id agent, const World* world_from, const World* world_to) const;
		bool				is_true(const World_Id& world_id, const Proposition_Instance* proposition) const;
		bool				is_world_designated(World_Id world) const;
		void				shift_perspective(const Agent* agent, bool is_exclusive=false);
		std::vector<State>	split_into_globals() const;
		void				set_single_designated(World_Id world);
		bool				valuate(const Formula& formula, const Domain& domain) const;
		bool				valuate(const Formula& formula, const Domain& domain, const World_Id& designated_world) const;

		bool operator==(const State& other) const;
		size_t to_hash(const std::set<World_Id>& designated_worlds) const;
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