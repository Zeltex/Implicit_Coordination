#include "Graph.hpp"
#include "Formula.hpp"
#include <iostream>

#include "World.hpp"
#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "Action.hpp"
#include "Action_Event.hpp"
#include "DEL_Operations.hpp"

using namespace del;
//Action_Event&& create_event(State& state) {
//	//State state(2);
//	state.create_world();
//	state.create_world();
//	state.create_world();
//	state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
//	state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
//	state.add_true_propositions(World_Id{ 2 }, { "in(red,Box2)" });
//	for (size_t i = 0; i < 3; i++) {
//		for (size_t j = 0; j < 3; j++) {
//			state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
//		}
//	}
//
//	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });
//
//	state.add_designated_world(World_Id{ 1 });
//
//	Action action(Agent_Id{ 1 }, 2);
//	Formula_Creator fc;
//	Formula precondition(fc.f_prop("in(red,Box1)"));
//	//auto precondition2 = Formula(fc.f_prop("in(red,Box1)"));
//	//std::unordered_set<std::string> temp1;
//	//std::unordered_set<std::string> temp2;
//	Event_Id id{ 0 };
//	//Action_Event event(id, std::move(precondition), temp1, temp2);
//	//action.add_event(event);
//
//	return std::move(Action_Event(id, std::move(precondition), std::unordered_set<std::string>(), std::unordered_set<std::string>()));
//}

int main(int argc, char* argv[]) {
	using namespace del;
	// Agents, 0:Lasse, 1:Pepper
	{
	//	State state(2);
	//	/*
	//	state.create_world();
	//	state.create_world();
	//	state.create_world();
	//	state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
	//	state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
	//	state.add_true_propositions(World_Id{ 2 }, { "in(red,Box2)" });
	//	for (size_t i = 0; i < 3; i++) {
	//		for (size_t j = 0; j < 3; j++) {
	//			state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
	//		}
	//	}

	//	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });

	//	state.add_designated_world(World_Id{ 1 });

	//	Action action(Agent_Id{ 1 }, 2);
	//	Formula_Creator fc;
	//	Formula precondition(fc.f_prop("in(red,Box1)"));
	//	//auto precondition2 = Formula(fc.f_prop("in(red,Box1)"));
	//	//std::unordered_set<std::string> temp1;
	//	//std::unordered_set<std::string> temp2;
	//	Event_Id id{ 0 };
	//	//Action_Event event(id, std::move(precondition), temp1, temp2);
	//	//action.add_event(event);

	//	Action_Event event = Action_Event(id, std::move(precondition), std::unordered_set<std::string>(), std::unordered_set<std::string>());
	//	//Action_Event event = Action_Event(id, Formula(fc.f_prop("in(red,Box1)")), std::unordered_set<std::string>(), std::unordered_set<std::string>());
	//	action.add_event(event);
	//	//action.add_event(id, std::move(precondition), std::unordered_set<std::string>(), std::unordered_set<std::string>());
	//	//State new_state = perform_product_update(state, action);
	//	*/
	//	Action action(Agent_Id{ 1 }, 2);
	//	auto event = create_event(state);
	//	action.add_event(event);
	//	perform_product_update(state, action);
	}
	int temp = 0;

	return 0;
}

