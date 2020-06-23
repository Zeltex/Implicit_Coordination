#include "DEL_Operations.hpp"

namespace del {

	// TODO - Check definition of applicable, does there have to be at least one designated world left?
	State perform_product_update(const State& state, const Action& orig_action, const std::vector<Agent>& agents) {

		// TODO - Currently creates an entire copy could probably be done more efficiently
		Action action = create_perceive_observe_reachables(state, orig_action);

#ifdef DEBUG_PRINT
		std::ofstream file;
		file.open("../action.dot");
		file << "digraph G {\n" << action.to_graph(agents) << "}";
		file.close();
#endif 

		std::vector<World_Entry> new_worlds;
		State result(state.get_number_of_agents());

		for (auto& world : state.get_worlds()) {
			for (const auto& event : action.get_events()) {
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
		result.copy_perceivability_and_observability(state);
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
			result.push_back(std::move(new_state));
		}
		return result;
	}


	bool is_action_applicable(const State& state, const Action& action) {
		auto worlds = state.get_designated_world_reachables(action.get_owner());

		for (auto& world_id : worlds) {
			auto& world = state.get_world(world_id);
			bool found_applicable_event = false;
			for (auto event : action.get_events()) {
				if (world.valuate(event.get_preconditions())) {
					found_applicable_event = true;
				}
			}
			if (!found_applicable_event) {
				return false;
			}
		}
		return true;
	}

	bool are_states_bisimilar(const State& state1, const State& state2) {
		Bisimulation_Context bisimulation_context(state1, state2);
		return bisimulation_context.is_bisimilar();
	}

	Action create_perceive_observe_reachables(const State& state, const Action& action) {
		Action result(action);
		std::vector<size_t> agents;
		Agent_Id owner = action.get_owner();
		std::vector<Agent_Id> non_observers;

		for (size_t agent = 0; agent < state.get_number_of_agents(); agent++) {

			// Perceivers
			auto& perceivables = state.get_perceivables({ agent });
			if (find(perceivables.begin(), perceivables.end(), owner) != perceivables.end()) {
				for (auto& event : result.get_events()) {
					result.add_indistinguishability_relation({ agent }, event.get_id(), event.get_id());
				}
				continue;
			}

			// Observers
			auto& observables = state.get_observables({ agent });
			if (find(observables.begin(), observables.end(), owner) != observables.end()) {
				for (auto& event1 : result.get_events()) {
					for (auto& event2 : result.get_events()) {
						result.add_indistinguishability_relation({ agent }, event1.get_id(), event2.get_id());
					}
				}
				continue;
			}

			non_observers.push_back({ agent });
		}

		if (!non_observers.empty()) {
			Formula preconditions;
			preconditions.f_top();
			Event_Id empty_event = result.get_events().size();
			result.add_event(std::string("unobservable"), Event_Id{ empty_event }, std::move(preconditions), {}, {});

			for (size_t agent = 0; agent < state.get_number_of_agents(); agent++) {
				result.add_indistinguishability_relation({ agent }, empty_event, empty_event);
			}

			// Un-awares
			for (auto& agent : non_observers) {
				for (auto& event : result.get_events()) {
					if (!(event.get_id() == empty_event)) {
						result.add_indistinguishability_relation({ agent }, event.get_id(), empty_event);
					}
				}
			}
		}
		return std::move(result);
	}
}