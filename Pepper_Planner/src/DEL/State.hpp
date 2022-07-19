#pragma once

#include "Accessibility_Relation.hpp"
#include "Formula.hpp"
#include "Proposition_Instance.hpp"
#include "Types.hpp"
#include "World.hpp"

#include <set>
#include <vector>
#include <optional>

namespace del
{

	class Action;
	class Agent;
	class Agents;
	class Atom_Lookup;
	class Domain;
	class General_State;
	class State
	{
	public:
		State(const std::vector<World>& worlds, const Accessibility_Relations& accessbility_relations, const std::set<World_Id>& designated_worlds, size_t cost);
		State(std::vector<World>&& worlds, Accessibility_Relations&& accessbility_relations, std::set<World_Id>&& designated_worlds, size_t cost);
		State(const State& other, World_Id designated_world);
		State(const General_State& other, const Propositions_Lookup& propositions_lookup, const Agents& agents, const Atom_Lookup& atom_lookup);

		const Agents*				get_agents() const;
		size_t						get_cost() const;
		const std::set<World_Id>&	get_designated_worlds() const;
		std::set<World_Id>			get_reachable_worlds(const Agent* agent) const;
		std::set<World_Id>			get_reachable_worlds(const Agent* agent, World_Id world_id) const;
		const World&				get_world(World_Id world) const;
		const std::vector<World>&	get_worlds() const;
		
		State					contract(const std::set<World_Id>& designated_worlds) const;
		State					contract() const;
		bool					is_one_reachable(Agent_Id agent, World_Id world_from, World_Id world_to) const;
		bool					is_one_reachable(Agent_Id agent, const World* world_from, const World* world_to) const;
		bool					is_valid() const;
		std::optional<State>	product_update(const Action* action, const Domain& domain) const;
		std::optional<State>	product_update(const Action* action, const Domain& domain, const std::set<World_Id>& designated_worlds) const;
		State					shift_and_contract(const Agent* agent) const;
		std::vector<State>		split_into_globals() const;
		size_t					to_hash(const std::set<World_Id>& designated_worlds) const;
		size_t					to_hash() const;
		std::string				to_string() const;
		std::string				to_string(size_t indentation) const;
		bool					valuate(const Formula& formula, const Domain& domain) const;
		bool					valuate(const Formula& formula, const Domain& domain, const World* designated_world) const;

		bool operator==(const State& other) const;


	private:

		size_t cost;
		std::vector<World> worlds;
		std::set<World_Id> designated_worlds;
		Accessibility_Relations accessibility_relations;
	};
}