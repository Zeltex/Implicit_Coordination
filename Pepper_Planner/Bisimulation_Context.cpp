#include "Bisimulation_Context.hpp"
#include <set>

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
		size_t block_counter = 0;
		std::vector<std::vector<World_Id>> worlds_to_be_moved;
		std::vector < std::vector<size_t>> index_to_be_erased;
		for (auto& block : blocks) {
			worlds_to_be_moved.emplace_back();
			index_to_be_erased.emplace_back();
			if (block.empty()) {
				continue;
			}
			size_t base_world = block[0].id;
			size_t counter = 0;
			for (auto& block_entry : block) {
				for (size_t i = 0; i < indistinguishability_relation.size(); i++) {
					if (!are_relations_equal(indistinguishability_relation[i][base_world], indistinguishability_relation[i][block_entry.id])) {
						worlds_to_be_moved[block_counter].push_back(block_entry);
						index_to_be_erased[block_counter].push_back(counter);
						blocks_changed = true;
						break;
					}
				}
				counter++;
			}
			block_counter++;
		}
		for (size_t i = 0; i < worlds_to_be_moved.size(); ++i) {
			for (auto it = index_to_be_erased[i].rbegin(); it != index_to_be_erased[i].rend(); ++it) {
				this->blocks[i].erase(this->blocks[i].begin() + *it);

			}
			if (!worlds_to_be_moved[i].empty()) {
				move_worlds_to_new_block(worlds_to_be_moved[i]);
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

		// TODO - I believe this should evaluate based on world true propositions rather than world ids
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

		for (const auto& block : blocks) {
			bool contains_world_from_state1 = false;
			bool contains_world_from_state2 = false;
			bool contains_designated_from_state1 = false;
			bool contains_designated_from_state2 = false;

			for (const auto& world : block) {
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


	// TODO - Split this into around a billion seperate methods
	State Bisimulation_Context::to_bisimulation_contraction(const State& state, size_t k) {

		// [world_from][agent][world_to]
		std::unordered_map <size_t, std::vector<std::vector<size_t>>> relations;
		for (size_t i = 0; i < state.get_worlds_count(); ++i) {
			relations[i] = std::vector < std::vector<size_t>>(state.get_number_of_agents());
		}
		size_t agent = 0;
		for (auto& relation : state.get_indistinguishability_relations()) {
			for (auto& entry : relation) {
				if (relations.find(entry.world_from.id) == relations.end()) {
					relations.insert({ entry.world_from.id, std::vector<std::vector<size_t>>(state.get_number_of_agents()) });
				}
				relations[entry.world_from.id][agent].emplace_back(entry.world_to.id);
			}
			agent++;
		}

		std::unordered_map<std::string, size_t> valuation_to_block;
		std::vector<std::string> valuations;
		valuations.reserve(state.get_worlds().size());

		// Get and sort valuations
		for (auto& world : state.get_worlds()) {
			std::string valuation = convert_propositions_to_string(world.get_true_propositions());
			if (std::find(valuations.begin(), valuations.end(), valuation) == valuations.end()) {
				valuations.push_back(valuation);
			}
		}
		std::sort(valuations.begin(), valuations.end());

		// Initialise blocks
		blocks = std::vector<std::vector<World_Id>>(valuations.size());
		size_t block_counter = 0;
		for (auto& valuation : valuations) {
			valuation_to_block[valuation] = block_counter;
			++block_counter;
		}

		for (const auto& world : state.get_worlds()) {
			// Set block/world mapping
			std::string valuation = convert_propositions_to_string(world.get_true_propositions());
			blocks[valuation_to_block[valuation]].push_back(world.get_id());
			world_to_block[world.get_id().id] = valuation_to_block[valuation];
		}


		partition_into_relations_blocks_contraction(relations, state.get_number_of_agents(), state.get_worlds_count());


		State result(state.get_number_of_agents());
		result.set_cost(state.get_cost());
		std::unordered_map<size_t, World_Id> block_to_new_world;

		std::vector<std::vector<std::set<size_t>>> block_relations(state.get_number_of_agents(), std::vector<std::set<size_t>>(state.get_worlds_count()));

		// Create block relations
		for (auto& old_world_entry : relations) {
			size_t agent = 0;
			size_t block_from = world_to_block[old_world_entry.first];
			for (auto& agent_entry : old_world_entry.second) {
				for (auto& old_world_to : agent_entry) {
					auto block_to = world_to_block[old_world_to];
					block_relations[agent][block_from].insert(block_to);
				}
				++agent;
			}
		}

		// Create new worlds
		for (size_t block = 0; block < this->blocks.size(); ++block) {
			auto& world = result.create_world();
			block_to_new_world[block] = world.get_id();
			world.add_true_propositions(state.get_world(blocks[block][0]).get_true_propositions());
		}

		// Create new world relations
		size_t agent_size = block_relations.size();
		for (size_t agent = 0; agent < agent_size; ++agent) {
			size_t from_size = block_relations[agent].size();
			for (size_t block_from = 0; block_from < from_size; ++block_from) {
				for (auto& block_to : block_relations[agent][block_from]) {
					auto& world_from = block_to_new_world[block_from];
					auto& world_to = block_to_new_world[block_to];

					result.add_indistinguishability_relation({ agent }, { world_from }, { world_to });
				}
			}
		}

		// Set designated worlds
		std::unordered_set<size_t> visited;
		visited.reserve(state.get_designated_worlds_count());
		for (auto& designated_world : state.get_designated_worlds()) {
			auto& block = world_to_block[designated_world.id];
			auto& world = block_to_new_world[block];
			if (visited.find(world.id) == visited.end()) {
				visited.insert(world.id);
				result.add_designated_world(world);
			}
		}
		return result;
	}

	void Bisimulation_Context::partition_into_relations_blocks_contraction(const std::unordered_map <size_t, std::vector<std::vector<size_t>>>& relations, size_t agents_size, size_t worlds_size) {
		size_t block_counter = 0;
		std::vector<std::vector<Signature>> blocks_to_be_created;


		std::vector<std::set<size_t>> blocks_to_be_deleted(this->blocks.size());
		for (auto& block : this->blocks) {

			// Record signatures
			std::vector<Signature> signatures;
			size_t counter_entry = 0;
			for (auto& block_entry : block) {
				signatures.emplace_back(block_counter, counter_entry, block_entry, (*relations.find(block_entry.id)).second, agents_size, worlds_size);
				counter_entry++;
			}
			std::sort(signatures.begin(), signatures.end());

			// Note blocks to be created
			std::vector<Signature> new_block;
			for (auto& signature : signatures) {
				if (new_block.empty() || new_block.at(0) == signature) {
					new_block.emplace_back(signature);
				} else {
					for (auto& entry : new_block) {
						blocks_to_be_deleted[block_counter].insert(entry.index_in_block);
					}
					blocks_to_be_created.push_back(std::move(new_block));
					new_block = { signature };
				}
			}
			++block_counter;
		}

		// Erase worlds from existing blocks
		for (size_t i = 0; i < blocks_to_be_deleted.size(); ++i) {
			auto& block = blocks_to_be_deleted.at(i);
			for (auto entry = block.rbegin(); entry != block.rend(); ++entry) {
				auto& temp_block = this->blocks.at(i);
				temp_block.erase(temp_block.begin() + *entry);
			}
		}

		// Create new blocks
		for (auto& block : blocks_to_be_created) {
			this->blocks.emplace_back();
			for (auto& block_entry : block) {
				blocks.back().push_back(block_entry.world);
				world_to_block[block_entry.world.id] = blocks.size() - 1;
			}
		}

		// Recurse
		if (!blocks_to_be_created.empty()) {
			partition_into_relations_blocks_contraction(relations, agents_size, worlds_size);
		}
	}

	std::string Bisimulation_Context::convert_propositions_to_string(const std::vector<Proposition_Instance>& propositions) {
		std::vector<std::string> vector_propositions;
		vector_propositions.reserve(propositions.size());
		for (auto& proposition : propositions) {
			vector_propositions.push_back(proposition.to_simple_string());
		}
		std::sort(vector_propositions.begin(), vector_propositions.end());
		std::string result;
		for (auto& proposition : vector_propositions) {
			result += proposition;
		}
		return result;
	}
	
}