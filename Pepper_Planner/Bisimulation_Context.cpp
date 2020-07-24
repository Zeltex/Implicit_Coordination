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

	State Bisimulation_Context::to_bisimulation_contraction(const State& state, size_t k) {
		std::unordered_set<size_t> visited;
		visited.reserve(state.get_worlds_count());
		std::deque<std::pair<size_t, size_t>> frontier;

		// Initial frontier
		for (const auto& world : state.get_designated_worlds()) {
			frontier.push_back({ world.id, 0});
		}

		// [world_from][agent][world_to]
		std::unordered_map <size_t, std::vector<std::vector<size_t>>> relations;
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

		// Get valuation partitions
		std::unordered_map<std::string, size_t> valuation_to_block;
		while (!frontier.empty()) {

			// Handle frontier/visited
			auto[current_world, depth] = frontier.front();
			frontier.pop_front();

			// Valuation
			std::string valuation = convert_propositions_to_string(state.get_world({ current_world }).get_true_propositions());
			if (valuation_to_block.find(valuation) == valuation_to_block.end()) {
				blocks.emplace_back();
				valuation_to_block[valuation] = blocks.size() - 1;
			}

			// Set block/world mapping
			blocks[valuation_to_block[valuation]].push_back({ current_world });
			world_to_block[current_world] = valuation_to_block[valuation];

			// Add children to frontier
			//if (depth < k) {
				for (auto& agent_entry : relations[current_world]) {
					for (auto& world_to : agent_entry) {
						if (visited.find(world_to) == visited.end()) {
							frontier.push_back({ world_to, depth + 1 });
							visited.insert(world_to);
						}
					}
				}
			//}

		}
		partition_into_relations_blocks_contraction(relations);


		State result(state.get_number_of_agents());
		result.set_cost(state.get_cost());
		std::unordered_map<size_t, World_Id> block_to_new_world;

		// Limit to k depth
		frontier.clear();
		visited.clear();
		std::unordered_set<size_t> temp_blocks_visited;
		for (auto& world : state.get_designated_worlds()) {
			auto& temp_block = world_to_block[world.id];
			if (visited.find(temp_block) == visited.end()) {
				frontier.push_back({ temp_block, 0 });
				visited.insert(temp_block);
				auto& world = result.create_world();
				block_to_new_world[temp_block] = world.get_id();
				world.add_true_propositions(state.get_world( world.get_id() ).get_true_propositions());
			}
		}
		while (!frontier.empty()) {

			// Handle frontier/visited
			auto [current_block, depth] = frontier.front();
			frontier.pop_front();
			const auto& current_old_world = blocks[current_block][0];
			

			// Add children to frontier
			if (depth < k) {
				size_t agent = 0;
				for (auto& agent_entry : relations[current_old_world.id]) {
					temp_blocks_visited.clear();
					for (auto& old_world_to : agent_entry) {
						auto block_to = world_to_block[old_world_to];
						if (visited.find(block_to) == visited.end()) {
							frontier.push_back({ block_to, depth + 1 });
							visited.insert(block_to);
							auto& world = result.create_world();
							block_to_new_world[block_to] = world.get_id();
							world.add_true_propositions(state.get_world({ old_world_to }).get_true_propositions());
						}
						if (temp_blocks_visited.find(block_to) == temp_blocks_visited.end()) {
							result.add_indistinguishability_relation({ agent }, { block_to_new_world[current_block] }, { block_to_new_world[block_to] });
							temp_blocks_visited.insert(block_to);
						}
					}
					agent++;
				}
			}
		}

		visited.clear();
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

	void Bisimulation_Context::partition_into_relations_blocks_contraction(const std::unordered_map <size_t, std::vector<std::vector<size_t>>>& relations) {
		bool blocks_changed = false;
		std::vector<std::vector<World_Id>> worlds_to_be_moved(this->blocks.size());
		std::vector<std::vector<size_t>> index_to_be_erased(this->blocks.size());
		size_t block_counter = 0;
		for (auto& block : this->blocks) {
			size_t base_world = block[0].id;
			size_t counter_entry = 0;
			for (auto& block_entry : block) {
				if (counter_entry != 0) {
					size_t agent = 0;
					auto agent_entries = relations.find(block_entry.id);

					// TODO - Is skipping empty entries, but should probably check those too
					for (auto& agent_entry : (*agent_entries).second) {
						if (!are_relations_equal(relations.at(base_world)[agent], agent_entry)) {
							worlds_to_be_moved[block_counter].push_back(block_entry);
							index_to_be_erased[block_counter].push_back(counter_entry);
							blocks_changed = true;
							break;

						}
						agent++;
					}
				}
				counter_entry++;
			}
			block_counter++;
		}
		for (size_t i = 0; i < index_to_be_erased.size(); i++) {
			for (auto j = index_to_be_erased[i].rbegin(); j != index_to_be_erased[i].rend(); j++) {
				this->blocks[i].erase(this->blocks[i].begin() + *j);
			}
			if (!worlds_to_be_moved[i].empty()) {
				move_worlds_to_new_block(worlds_to_be_moved[i]);
			}
		}
		if (blocks_changed) {
			partition_into_relations_blocks_contraction(relations);
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