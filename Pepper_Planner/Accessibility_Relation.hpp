#pragma once

#include <vector>
#include <set>
#include <map>

#include "Types.hpp"

namespace del
{
	struct Accessibility_Relation {
		Accessibility_Relation(size_t worlds_size) : worlds_size(worlds_size) {}
		Accessibility_Relation(const Accessibility_Relation& other, const std::map<World_Id, World_Id>& world_old_to_new);

		bool has_direct_relation(const World_Id& from_world, const World_Id& to_world) const;

		size_t get_index(const World_Id& from_world, const World_Id& to_world) const;
		size_t get_index(const size_t& from_world, const size_t& to_world) const;

		bool operator== (const Accessibility_Relation& other) const;
		bool operator!= (const Accessibility_Relation& other) const;

		void to_hashable_string(std::string& ref_result, size_t& ref_count) const;

		std::vector<bool> world_relations;
		size_t worlds_size;
	};

	class Accessibility_Relations
	{
	public:
		Accessibility_Relations(size_t world_count);
		std::set<World_Id> get_unreachable_worlds(const std::set<World_Id>& worlds) const;
		void convert_world_ids(const std::map<World_Id, World_Id>& world_old_to_new);
		bool has_direct_relation(const Agent_Id& agent, const World_Id& from_world, const World_Id& to_world) const;
		bool operator== (const Accessibility_Relations& other) const;		
		bool operator!= (const Accessibility_Relations& other) const;
		std::string to_hashable_string(size_t& ref_count) const;

	private:
		std::vector<Accessibility_Relation> agent_relations;
		size_t worlds_size;
	};
}