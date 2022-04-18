#include "DEL_Operations.hpp"
#include "Core.hpp"
#include "Formula_Input_Impl.hpp"

namespace del {

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