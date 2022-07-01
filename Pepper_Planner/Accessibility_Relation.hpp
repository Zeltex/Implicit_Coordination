#pragma once

#include <vector>
#include <set>
#include <map>
#include <string>

#include "Types.hpp"

namespace del
{
	class Action;
	class State;
	class Action_Event;
	class Domain;

	class Accessibility_Relations
	{
	public:
		Accessibility_Relations(size_t world_count, size_t agent_count);
		Accessibility_Relations(std::vector<bool>&& new_agent_relations, size_t world_count, size_t agent_count);
		std::set<World_Id> get_unreachable_worlds(const std::set<World_Id>& worlds) const;
		void convert_world_ids(const std::map<World_Id, World_Id>& world_old_to_new);
		bool has_direct_relation(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const;
		Accessibility_Relations product_update(const std::vector<World_Entry>& world_conversion, const Action& action, const Domain& domain, const State& state, const size_t& new_worlds_size) const;
		bool operator== (const Accessibility_Relations& other) const;		
		bool operator!= (const Accessibility_Relations& other) const;
		std::string to_hashable_string(size_t& ref_count) const;
		std::string to_string(const Domain& domain) const;
		void set(Agent_Id agent, World_Id world_from, World_Id world_to);
		size_t get_number_of_agents() const;
		size_t get_index(const size_t& agent, const size_t& from_world, const size_t& to_world) const;
		size_t get_index(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const;
		size_t get_index(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world, const size_t worlds_size, const size_t worlds_size_squared) const;
		bool is_serial_transitive_euclidean() const;

	private:
		std::vector<bool> relations;
		size_t worlds_size;
		size_t worlds_size_squared;
		size_t agents_size;
	};
}