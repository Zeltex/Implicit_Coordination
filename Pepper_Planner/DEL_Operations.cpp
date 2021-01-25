#include "DEL_Operations.hpp"
#include "Core.hpp"
#include "Formula_Input_Impl.hpp"
#include "Domain.hpp"

namespace del {

	State perform_product_update(const State& state, const Action& action, const std::vector<Agent>& agents, const Domain& domain) {
		State result(state.get_number_of_agents());
		result.set_cost(state.get_cost() + action.get_cost());
		Formula_Input_Impl input = { &state, &domain };

		size_t events_size = action.get_events().size();
		std::vector<std::vector<size_t>> new_relations(domain.get_amount_of_agents());
		const auto& state_relations = state.get_relations();
		const auto& action_relations = action.get_relations();
		size_t index_counter = 0;

		for (auto& world : state.get_worlds()) {
			for (const auto& event : action.get_events()) {
				if (event.get_preconditions().valuate(world.get_id().id, &input)) {

					bool designated = state.is_world_designated(world.get_id()) && action.is_event_designated(event.get_id());
					result.create_world(world, event, designated);

					for (size_t agent = 0; agent < state.get_number_of_agents(); ++agent) {
						size_t index = state_relations.get_class(world.get_id(), { agent }) * events_size + action_relations.get_class(event.get_id(), { agent });
						new_relations.at(agent).push_back(index);
						index_counter = std::max(index_counter, index);
					}
					result.set_relations({ new_relations, index_counter });
				}
			}
		}

		result.copy_perceivability_and_observability(state);
#if REMOVE_UNREACHABLE_WORLDS_ENABLED == 1
		result.remove_unreachable_worlds();
#endif
		return std::move(result);
	}

	State perform_perspective_shift(const State& state, Agent_Id agent_id) {

		auto new_designated = state.get_designated_world_reachables(agent_id);

		//std::vector<World_Id> frontier;
		//std::unordered_set<size_t> visited;
		//for (const auto& designated_world : state.get_designated_worlds()) {
		//	frontier.push_back(designated_world);
		//}
		//while (!frontier.empty()) {
		//	auto current = frontier.back();
		//	frontier.pop_back();
		//	for (const auto& relation : state.get_indistinguishability_relations(agent_id)) {
		//		if (relation.world_from == current &&
		//			std::find(visited.begin(), visited.end(), relation.world_to.id) == visited.end()) {

		//			frontier.push_back(relation.world_to);
		//			visited.insert(relation.world_to.id);
		//		}
		//	}
		//}
		//std::vector<World_Id> designated_worlds;
		//designated_worlds.reserve(visited.size());
		//for (auto& entry : visited) {
		//	designated_worlds.emplace_back(World_Id{ entry });
		//}

		State result = State(state);
		result.set_designated_worlds(new_designated);
		return std::move(result);
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

	//bool are_states_bisimilar(const State& state1, const State& state2) {
	//	Bisimulation_Context bisimulation_context(state1, state2);
	//	return bisimulation_context.is_bisimilar();
	//}


	State perform_k_bisimilar_contraction(const State& state, size_t depth) {
		State temp1;
		State temp2;
		Bisimulation_Context bisimulation_context(temp1, temp2);
		return bisimulation_context.to_bisimulation_contraction(state, depth);
	}
}