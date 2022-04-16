#include "DEL_Operations.hpp"
#include "Core.hpp"
#include "Formula_Input_Impl.hpp"

namespace del {

	// TODO - Check definition of applicable, does there have to be at least one designated world left?
	State perform_product_update(const State& state, const Action& action, const std::vector<Agent>& agents, const Domain& domain) {
		std::vector<World_Entry> new_worlds;
		State result(state.get_number_of_agents());
		result.set_cost(state.get_cost() + action.get_cost());
		Formula_Input_Impl input = { &state, &domain };

		for (auto& world : state.get_worlds()) {
			for (const auto& event : action.get_events()) {
				if (event.get_preconditions().valuate(world.get_id().id, &input)) {
					// TODO - Maybe handle unreachable worlds here

					World& updated_world = result.create_world();
					updated_world.add_true_propositions(world.get_true_propositions());
					updated_world.remove_true_propositions(event.get_delete_list());
					updated_world.add_true_propositions(event.get_add_list());

					if (state.is_world_designated(world.get_id()) && action.is_event_designated(event.get_id())) {
						result.set_world_designated(updated_world.get_id());
					}

					new_worlds.emplace_back(world.get_id(), event.get_id(), updated_world.get_id());
				}
			}
		}

		for (const auto& world1 : new_worlds) {
			for (const auto& world2 : new_worlds) {
				for (size_t i = 0; i < state.get_number_of_agents(); i++) {
					Agent_Id agent = Agent_Id{ i };
					if (state.is_one_reachable(agent, world1.old_world, world2.old_world) &&
						action.is_condition_fulfilled(agent, world1.old_event, world2.old_event, state, world1.old_world, domain)) {
						result.add_indistinguishability_relation(agent, world1.new_world, world2.new_world);
					}
				}
			}
		}
#if REMOVE_UNREACHABLE_WORLDS_ENABLED == 1
		result.remove_unreachable_worlds();
#endif
		return result;
	}
	// Using definition: All states reachable by 'agent' from any designated world, 
	// and the resulting worlds must be closed under 'agent' (any world should be reachable from any other world by 'agent')
	State perform_perspective_shift(const State& state, Agent_Id agent_id) {

		std::vector<World_Id> frontier;
		// Using size_t instead of World_Id to avoid specifying custom hash function for World_Id
		std::unordered_set<size_t> visited;
		for (const auto& designated_world : state.get_designated_worlds()) {
			frontier.push_back(designated_world);
		}
		while (!frontier.empty()) {
			auto current = frontier.back();
			frontier.pop_back();
			for (const auto& relation : state.get_indistinguishability_relations(agent_id)) {
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
		return result;
	}

	std::vector<State> split_into_global_states(const State& state, const Agent_Id agent) {
		std::vector<State> result;
		for (const auto& designated_world : state.get_designated_worlds()) {
			State new_state = State(state);
			new_state.set_single_designated_world(designated_world);
#if REMOVE_UNREACHABLE_WORLDS_ENABLED == 1
			new_state.remove_unreachable_worlds();
#endif
			result.push_back(std::move(new_state));
		}
		return result;
	}


	bool is_action_applicable(const State& state, const Action& action, const Domain& domain) {
		auto worlds = state.get_designated_world_reachables(action.get_owner());
		Formula_Input_Impl input = { &state, &domain };

		for (auto& world_id : worlds) {
			bool found_applicable_event = false;
			for (const auto& event : action.get_events()) {
				if (action.is_event_designated(event.get_id().id) && event.get_preconditions().valuate(world_id.id, &input)) {
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
		State contracted_state1 = bisimulation_context::contract(state1);
		State contracted_state2 = bisimulation_context::contract(state2);
		return contracted_state1 == contracted_state2;
	}

	State perform_bisimilar_contraction(const State& state)
	{
		return bisimulation_context::contract(state);
	}
}