#include "Environment_Loader.hpp"

namespace del {
	std::tuple<Domain, Action_Library, Formula> Environment_Loader::load(size_t environment_number) {
	//	switch (environment_number) {
	//	case 0: return load_0();
	//	default: return load_0();
	//	}
		return {};
	}

	//std::tuple<Domain, Action_Library, Formula> Environment_Loader::load_0() {
	//	size_t amount_of_agents = 2;

	//	Formula goal = get_goal_formula();
	//	State state = get_initial_state(amount_of_agents);
	//	Action_Library library;
	//	library.set_amount_of_agents(amount_of_agents);
	//	add_actions(library, amount_of_agents);

	//	Domain domain(amount_of_agents, state);

	//	return { domain, library, std::move(goal) };
	//}

	//Formula Environment_Loader::get_goal_formula() {

	//	Formula f;
	//	f.f_prop({ "in", { "red","L" } });
	//	return std::move(f);
	//}


	//void Environment_Loader::add_announce_action(Action_Library& library, Proposition_Instance proposition, size_t amount_of_agents) {
	//	Action action(Agent_Id{ 0 }, 2);
	//	Formula f;
	//	f.f_prop(proposition);
	//	Action_Event event = Action_Event(Event_Id { 0 }, std::move(f), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
	//	action.add_event(event);
	//	action.add_designated_event(Event_Id{ 0 });
	//	action.add_indistinguishability_relation(Agent_Id{ 0 }, Event_Id{ 0 }, Event_Id{ 0 });
	//	action.add_indistinguishability_relation(Agent_Id{ 1 }, Event_Id{ 0 }, Event_Id{ 0 });

	//	library.add_action(action);
	//}

	//void Environment_Loader::add_pickup_action(Action_Library& library, Proposition_Instance from, Proposition_Instance to, size_t amount_of_agents) {
	//	Action action(Agent_Id{ 1 }, 2);
	//	Formula f;
	//	f.f_prop(from);

	//	Action_Event event = Action_Event(Event_Id { 0 }, std::move(f), { to }, { from });
	//	action.add_event(event);
	//	action.add_designated_event(Event_Id{ 0 });

	//	action.add_indistinguishability_relation(Agent_Id{ 0 }, Event_Id{ 0 }, Event_Id{ 0 });
	//	action.add_indistinguishability_relation(Agent_Id{ 1 }, Event_Id{ 0 }, Event_Id{ 0 });
	//	library.add_action(action);
	//}


	//void Environment_Loader::add_perceive_action(Action_Library& library, Proposition_Instance proposition, size_t amount_of_agents) {
	//	Action action(Agent_Id{ 1 }, 2);
	//	Formula f;
	//	f.f_prop(proposition);
	//	std::vector<Proposition_Instance> add_list = { };
	//	std::vector<Proposition_Instance> del_list = { };
	//	Action_Event event = Action_Event(Event_Id { 0 }, std::move(f), add_list, del_list);

	//	Formula f2;
	//	f2.f_not(f2.f_prop(proposition));
	//	std::vector<Proposition_Instance> add_list2 = { };
	//	std::vector<Proposition_Instance> del_list2 = { };
	//	Action_Event event2 = Action_Event(Event_Id { 1 }, std::move(f2), add_list2, del_list2);

	//	action.add_event(event);
	//	action.add_event(event2);
	//	action.add_designated_event(Event_Id{ 0 });
	//	action.add_designated_event(Event_Id{ 1 });

	//	for (size_t i = 0; i < 2; i++) {
	//		action.add_indistinguishability_relation(Agent_Id{ 0 }, Event_Id{ i }, Event_Id{ i });
	//		action.add_indistinguishability_relation(Agent_Id{ 1 }, Event_Id{ i }, Event_Id{ i });
	//	}

	//	library.add_action(action);
	//}

	//void Environment_Loader::add_actions(Action_Library& library, size_t amount_of_agents) {
	//	add_announce_action(library, { "in", { "red","Box0" } }, amount_of_agents);
	//	add_announce_action(library, { "in", { "red","Box1" } }, amount_of_agents);
	//	add_announce_action(library, { "in", { "red","Box2" } }, amount_of_agents);

	//	add_pickup_action(library, { "in", { "red","Box0" } }, { "in", { "red","L" } }, amount_of_agents);
	//	add_pickup_action(library, { "in", { "red","Box1" } }, { "in", { "red","L" } }, amount_of_agents);
	//	add_pickup_action(library, { "in", { "red","Box2" } }, { "in", { "red","L" } }, amount_of_agents);

	//	add_perceive_action(library, { "in", { "red","Box0" } }, amount_of_agents);
	//	add_perceive_action(library, { "in", { "red","Box1" } }, amount_of_agents);
	//	add_perceive_action(library, { "in", { "red","Box2" } }, amount_of_agents);
	//}


	//State Environment_Loader::get_initial_state(size_t amount_of_agents) {
	//	// Agents 0:L  1:Pepper

	//	State state(amount_of_agents);
	//	state.create_worlds(3);
	//	state.add_true_propositions(World_Id{ 0 }, { {"in", {"red", "Box0"} } });
	//	state.add_true_propositions(World_Id{ 1 }, { {"in", {"red", "Box1"} } });
	//	state.add_true_propositions(World_Id{ 2 }, { {"in", {"red", "Box2"} } });

	//	for (size_t i = 0; i < 3; i++) {
	//		for (size_t j = 0; j < 3; j++) {
	//			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ j });
	//		}
	//	}

	//	state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 1 });

	//	state.set_world_designated(World_Id{ 1 });

	//	return state;
	//}
};