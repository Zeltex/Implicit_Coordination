#include "DEL_Operations.hpp"

namespace del {

	// TODO - Check definition of applicable, does there have to be at least one designated world left?
	State perform_product_update(State& state, Action& action) {
		//Agent_Id agent = action.get_owner();
		std::vector<World_Entry> new_worlds;
		State result(state.get_number_of_agents());

		for (auto& world : state.get_worlds()) {
			for (auto& event : action.get_events()) {
				if (world.valuate(event.get_preconditions())) {
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
						action.is_one_reachable(agent, world1.old_event, world2.old_event)) {
						result.add_indistinguishability_relation(agent, world1.new_world, world2.new_world);
					}
				}
			}
		}
		return std::move(result);
	}
	State perform_perspective_shift(State state, Agent agent) {
		throw;
	}
	std::vector<State> split_into_global_states(State state) {
		throw;
	}
}