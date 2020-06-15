#include "Bisimulation_Context.hpp"

namespace del {
	void Bisimulation_Context::create_merged_worlds_list() {
		worlds = std::vector<World>();
		for (auto& world : state1.get_worlds()) {
			size_t id = worlds.size();
			worlds.emplace_back(World_Id{ id }, world.get_true_propositions());
			old_to_new_world1[world.get_id().id] = id;
			is_world_from_state1[id] = true;
			is_world_designated[id] = false;
		}
		for (auto& world : state2.get_worlds()) {
			size_t id = worlds.size();
			worlds.emplace_back(World_Id{ id }, world.get_true_propositions());
			old_to_new_world2[world.get_id().id] = id;
			is_world_from_state1[id] = false;
			is_world_designated[id] = false;
		}

		for (auto& world : state1.get_designated_worlds()) {
			is_world_designated[old_to_new_world1[world.id]] = true;
		}
		for (auto& world : state2.get_designated_worlds()) {
			is_world_designated[old_to_new_world2[world.id]] = true;
		}
	}

	void Bisimulation_Context::create_merged_relations_list() {
		for (size_t agent = 0; agent < state1.get_number_of_agents(); agent++) {
			indistinguishability_relation.emplace_back();
			for (auto& relation : state1.get_indistinguishability_relations(Agent_Id{ agent })) {
				auto& world_from = old_to_new_world1[relation.world_from.id];
				auto& world_to = old_to_new_world1[relation.world_to.id];
				if (indistinguishability_relation[agent].find(world_from) != indistinguishability_relation[agent].end()) {
					indistinguishability_relation[agent][world_from].push_back(world_to);
				} else {
					indistinguishability_relation[agent][world_from] = { world_to };
				}
			}
			for (auto& relation : state2.get_indistinguishability_relations(Agent_Id{ agent })) {
				auto& world_from = old_to_new_world2[relation.world_from.id];
				auto& world_to = old_to_new_world2[relation.world_to.id];


				if (indistinguishability_relation[agent].find(world_from) != indistinguishability_relation[agent].end()) {
					indistinguishability_relation[agent][world_from].push_back(world_to);
				}
				else {
					indistinguishability_relation[agent][world_from] = { world_to };
				}
			}
		}
	}

	void Bisimulation_Context::partition_into_valuation_blocks() {
		std::unordered_map<std::string, std::vector<World_Id>> valuation_partitions;
		for (auto& world : worlds) {
			std::string valuation = convert_propositions_to_string(world.get_true_propositions());
			if (valuation_partitions.find(valuation) != valuation_partitions.end()) {
				valuation_partitions[valuation].push_back(world.get_id());
			} else {
				valuation_partitions[valuation] = { world.get_id() };
			}
		}

		for (auto& valuation_partition : valuation_partitions) {
			blocks.emplace_back();
			size_t block = blocks.size() - 1;
			for (auto& partition_world : valuation_partition.second) {
				blocks[block].push_back(partition_world);
				world_to_block[partition_world.id] = block;
			}
		}
	}

	// TODO - Could be optimised
	void Bisimulation_Context::partition_into_relations_blocks() {
		bool blocks_changed = false;
		for (auto& block : blocks) {
			if (block.empty()) {
				continue;
			}
			std::vector<World_Id> worlds_to_be_moved;
			std::vector<size_t> index_to_be_erased;
			size_t base_world = block[0].id;
			size_t counter = 0;
			for (auto& block_entry : block) {
				for (size_t i = 0; i < indistinguishability_relation.size(); i++) {
					if (!are_relations_equal(indistinguishability_relation[i][base_world], indistinguishability_relation[i][block_entry.id])) {
						worlds_to_be_moved.push_back(block_entry);
						index_to_be_erased.push_back(counter);
						blocks_changed = true;
						break;
					}
				}
				counter++;
			}
			for (int i = index_to_be_erased.size() - 1; i >= 0; i--) {
				block.erase(block.begin() + index_to_be_erased[i]);
			
			}
			//for (auto erase_index : index_to_be_erased) {
			//	block.erase(block.begin() + erase_index);
			//}
			if (!worlds_to_be_moved.empty()) {
				move_worlds_to_new_block(worlds_to_be_moved);
			}
		}
		if (blocks_changed) {
			partition_into_relations_blocks();
		}
	}

	bool Bisimulation_Context::are_relations_equal(std::vector<size_t> original_relations1, std::vector<size_t> original_relations2) {
		std::vector<size_t> relations1;
		for (size_t entry : original_relations1) {
			relations1.push_back(world_to_block[entry]);
		}
		std::vector<size_t> relations2;
		for (size_t entry : original_relations2) {
			relations2.push_back(world_to_block[entry]);
		}

		std::sort(relations1.begin(), relations1.end());
		std::sort(relations2.begin(), relations2.end());
		relations1.erase(std::unique(relations1.begin(), relations1.end()), relations1.end());
		relations2.erase(std::unique(relations2.begin(), relations2.end()), relations2.end());
		if (relations1.size() != relations2.size()) {
			return false;
		}
		for (size_t i = 0; i < relations1.size(); i++) {
			if (relations1[i] != relations2[i]) {
				return false;
			}
		}
		return true;
	}

	void Bisimulation_Context::move_worlds_to_new_block(const std::vector<World_Id>& worlds_to_be_moved) {
		std::vector<World_Id> worlds_different_than_base;
		std::vector<World_Id> worlds_same_as_base;
		size_t base_world = worlds_to_be_moved[0].id;
		worlds_same_as_base.push_back(worlds_to_be_moved[0]);
		size_t counter = 0;
		bool first = true;

		for (auto& block_entry : worlds_to_be_moved) {
			if (first) {
				first = false;
			} else {
				bool is_different = false;
				for (size_t i = 0; i < indistinguishability_relation.size(); i++) {
					if (!are_relations_equal(indistinguishability_relation[i][base_world], indistinguishability_relation[i][block_entry.id])) {
						worlds_different_than_base.push_back(block_entry);
						is_different = true;
						break;
					}
				}
				if (!is_different) {
					worlds_same_as_base.push_back(block_entry);
				}
			}
			counter++;
		}

		blocks.emplace_back();
		for (auto world : worlds_same_as_base) {
			blocks.back().push_back(world);
			world_to_block[world.id] = blocks.size() - 1;
		}

		if (!worlds_different_than_base.empty()) {
			move_worlds_to_new_block(worlds_different_than_base);
		}
	}

	bool Bisimulation_Context::is_bisimilar() {
		if (state1.get_number_of_agents() != state2.get_number_of_agents()) {
			return false;
		}
		create_merged_worlds_list();
		create_merged_relations_list();
		partition_into_valuation_blocks();
		partition_into_relations_blocks();

		// TODO - Should also check if all designated worlds has corresponding designated world from the other state
		for (auto& block : blocks) {
			bool contains_world_from_state1 = false;
			bool contains_world_from_state2 = false;
			bool contains_designated_from_state1 = false;
			bool contains_designated_from_state2 = false;
			
			for (auto& world : block) {
				if (is_world_from_state1[world.id]) {
					contains_world_from_state1 = true;
					if (is_world_designated[world.id]) {
						contains_designated_from_state1 = true;
					}
				} else {
					contains_world_from_state2 = true;
					if (is_world_designated[world.id]) {
						contains_designated_from_state2 = true;
					}
				}
			}
			if (!contains_world_from_state1 
				|| !contains_world_from_state2 
				|| (contains_designated_from_state1 && !contains_designated_from_state2)
				|| (!contains_designated_from_state1 && contains_designated_from_state2)) {
				return false;
			}
		}
		return true;
	}

	std::string Bisimulation_Context::convert_propositions_to_string(const std::unordered_set<std::string>& propositions) {
		std::vector < std::string> vector_propositions;
		for (auto& proposition : propositions) {
			vector_propositions.push_back(proposition);
		}
		std::sort(vector_propositions.begin(), vector_propositions.end());
		std::string result;
		for (auto& proposition : vector_propositions) {
			result += proposition;
		}
		return result;
	}
	
}