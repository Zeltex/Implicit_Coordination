#include "DEL_Operations.hpp"

namespace del {

	// TODO - Check definition of applicable, does there have to be at least one designated world left?
	State perform_product_update(const State& state, const Action& action, const std::vector<Agent>& agents) {
		std::vector<World_Entry> new_worlds;
		State result(state.get_number_of_agents());
		result.set_cost(state.get_cost() + action.get_cost());

		for (auto& world : state.get_worlds()) {
			for (const auto& event : action.get_events()) {
				if (event.get_preconditions().valuate(world.get_id().id, &state)) {
					// TODO - Maybe handle unreachable worlds here

					World& updated_world = result.create_world();
					updated_world.add_true_propositions(world.get_true_propositions());
					updated_world.remove_true_propositions(event.get_delete_list());
					updated_world.add_true_propositions(event.get_add_list());

					if (state.is_world_designated(world.get_id()) && action.is_event_designated(event.get_id())) {
						result.add_designated_world(updated_world.get_id());
					}

					new_worlds.emplace_back(world.get_id(), event.get_id(), updated_world.get_id());
				}
			}
		}

		for (auto world1 : new_worlds) {
			for (auto world2 : new_worlds) {
				for (size_t i = 0; i < state.get_number_of_agents(); i++) {
					Agent_Id agent = Agent_Id{ i };
					if (state.is_one_reachable(agent, world1.old_world, world2.old_world) &&
						action.is_condition_fulfilled(agent, world1.old_event, world2.old_event, state, world1.old_world)) {
						result.add_indistinguishability_relation(agent, world1.new_world, world2.new_world);
					}
				}
			}
		}
		result.copy_perceivability_and_observability(state);
		result.remove_unreachable_worlds();
		return std::move(result);
	}
	// Using definition: All states reachable by 'agent' from any designated world, 
	// and the resulting worlds must be closed under 'agent' (any world should be reachable from any other world by 'agent')
	State perform_perspective_shift(const State& state, Agent_Id agent_id) {

		std::vector<World_Id> frontier;
		// Using size_t instead of World_Id to avoid specifying custom hash function for World_Id
		std::unordered_set<size_t> visited;
		for (auto designated_world : state.get_designated_worlds()) {
			frontier.push_back(designated_world);
		}
		while (!frontier.empty()) {
			auto current = frontier.back();
			frontier.pop_back();
			for (auto relation : state.get_indistinguishability_relations(agent_id)) {
				if (relation.world_from == current &&
					std::find(visited.begin(), visited.end(), relation.world_to.id) == visited.end()) {

					frontier.push_back(relation.world_to);
					visited.insert(relation.world_to.id);
				}
			}
		}
		std::vector<World_Id> designated_worlds;
		designated_worlds.reserve(visited.size());
		for (auto& entry : visited) {
			designated_worlds.emplace_back(World_Id{ entry });
		}

		State result = State(state);
		result.set_designated_worlds(designated_worlds);
		return std::move(result);
	}

	std::vector<State> split_into_global_states(const State& state, const Agent_Id agent) {
		std::vector<State> result;
		for (auto designated_world : state.get_designated_worlds()) {
			State new_state = State(state);
			new_state.set_single_designated_world(designated_world);
			new_state.remove_unreachable_worlds();
			result.push_back(std::move(new_state));
		}
		return result;
	}


	bool is_action_applicable(const State& state, const Action& action) {
		auto worlds = state.get_designated_world_reachables(action.get_owner());

		for (auto& world_id : worlds) {
			bool found_applicable_event = false;
			for (auto event : action.get_events()) {
				if (event.get_preconditions().valuate(world_id.id, &state)) {
					found_applicable_event = true;
					break;
				}
			}
			if (!found_applicable_event) {
				return false;
			}
		}
		return !worlds.empty();
	}

	bool are_states_bisimilar(const State& state1, const State& state2) {
		Bisimulation_Context bisimulation_context(state1, state2);
		return bisimulation_context.is_bisimilar();
	}


	State perform_k_bisimilar_contraction(const State& state, size_t depth) {
		State temp1;
		State temp2;
		Bisimulation_Context bisimulation_context(temp1, temp2);
		return bisimulation_context.to_bisimulation_contraction(state, depth);
	}
}