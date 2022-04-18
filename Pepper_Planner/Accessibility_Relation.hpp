#pragma once

#include <vector>
#include <set>
#include <map>

#include "Types.hpp"

namespace del
{
	class Action;
	class State;
	class Action_Event;
	class Domain;
	struct Accessibility_Relation {
		Accessibility_Relation(const Agent_Id& agent, size_t worlds_size);
		Accessibility_Relation(const Agent_Id& agent, const Accessibility_Relation& other, const std::map<World_Id, World_Id>& world_old_to_new);
		Accessibility_Relation(const Agent_Id& agent, const Accessibility_Relation& other,
			const std::vector<World_Entry>& world_conversion,
			const Action& action,
			const Domain& domain,
			const State& state);

		bool is_serial() const;
		bool is_transitive() const;
		bool is_euclidean() const;
		bool is_serial_transitive_euclidean() const;

		bool has_direct_relation(const World_Id& from_world, const World_Id& to_world) const;
		Accessibility_Relation product_update(const std::vector<std::pair<World_Id, World_Id>>& world_old_to_new) const;

		size_t get_index(const World_Id& from_world, const World_Id& to_world) const;
		size_t get_index(const size_t& from_world, const size_t& to_world) const;

		bool operator== (const Accessibility_Relation& other) const;
		bool operator!= (const Accessibility_Relation& other) const;

		void to_hashable_string(std::string& ref_result, size_t& ref_count) const;
		std::string to_string(const Domain& domain) const;
		void set(World_Id world_from, World_Id world_to);

		Agent_Id agent;
		size_t worlds_size;
		std::vector<bool> world_relations;
	};

	class Accessibility_Relations
	{
	public:
		Accessibility_Relations(size_t world_count, size_t agent_count);
		Accessibility_Relations(const std::vector<Accessibility_Relation>& new_agent_relations);
		std::set<World_Id> get_unreachable_worlds(const std::set<World_Id>& worlds) const;
		void convert_world_ids(const std::map<World_Id, World_Id>& world_old_to_new);
		bool has_direct_relation(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const;
		Accessibility_Relations product_update(const std::vector<World_Entry>& world_conversion, const Action& action, const Domain& domain, const State& state) const;
		bool operator== (const Accessibility_Relations& other) const;		
		bool operator!= (const Accessibility_Relations& other) const;
		std::string to_hashable_string(size_t& ref_count) const;
		std::string to_string(const Domain& domain) const;
		void set(Agent_Id agent, World_Id world_from, World_Id world_to);


		bool is_serial() const;
		bool is_transitive() const;
		bool is_euclidean() const;
		bool is_serial_transitive_euclidean() const;

	private:
		size_t worlds_size;
		std::vector<Accessibility_Relation> agent_relations;
	};
}