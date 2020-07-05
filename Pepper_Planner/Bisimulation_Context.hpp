#pragma once

#include <unordered_map>
#include <algorithm>

#include "State.hpp"
#include "Types.hpp"

namespace del {
	class Domain;
	class Bisimulation_Context {
	public:
		Bisimulation_Context(const State& state1, const State& state2) : state1(state1), state2(state2) {}

		void create_merged_worlds_list();
		void create_merged_relations_list();
		void partition_into_valuation_blocks();
		void partition_into_relations_blocks();
		bool are_relations_equal(std::vector<size_t> original_relations1, std::vector<size_t> original_relations2);
		void move_worlds_to_new_block(const std::vector<World_Id>& worlds_to_be_moved);
		bool is_bisimilar();
		std::string convert_propositions_to_string(const std::vector<Proposition_Instance>& propositions);
	private:
		State state1;
		State state2;
		std::unordered_map<size_t, size_t> old_to_new_world1;
		std::unordered_map<size_t, size_t> old_to_new_world2;
		std::unordered_map<size_t, bool> is_world_from_state1;
		std::unordered_map<size_t, bool> is_world_designated;
		std::vector<World> worlds;

		// TODO - Store relations more elegantly
		std::vector<std::unordered_map<size_t, std::vector<size_t>>> indistinguishability_relation;
		std::unordered_map<size_t, size_t> world_to_block;
		std::vector<std::vector<World_Id>> blocks;
	};
}