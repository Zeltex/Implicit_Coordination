#include "Graph.hpp"
#include "Formula.hpp"
#include <iostream>

#include "World.hpp"
#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "Action.hpp"
#include "Action_Event.hpp"
#include "DEL_Operations.hpp"
#include "Action_Library.hpp"
#include "Planner.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"

using namespace del;


Formula get_goal_formula() {
	
	Formula f;
	f.f_prop("in(red,L)");
	return std::move(f);
}


void add_announce_action(Action_Library& library, std::string proposition, size_t amount_of_agents) {
	Action action(Agent_Id{ 1 }, 2);
	Formula f;
	f.f_prop(proposition);
	Action_Event event = Action_Event(Event_Id { 0 }, std::move(f), std::unordered_set<std::string>(), std::unordered_set<std::string>());
	action.add_event(event);
	action.add_designated_event(Event_Id{ 0 });
	action.add_indistinguishability_relation(Agent_Id{ 0 }, Event_Id{ 0 }, Event_Id{ 0 });
	action.add_indistinguishability_relation(Agent_Id{ 1 }, Event_Id{ 0 }, Event_Id{ 0 });

	library.add_action(action);
}

void add_pickup_action(Action_Library& library, std::string from, std::string to, size_t amount_of_agents) {
	Action action(Agent_Id{ 0 }, 2);
	Formula f;
	f.f_prop(from);

	Action_Event event = Action_Event(Event_Id { 0 }, std::move(f), { to }, { from });
	action.add_event(event);
	action.add_designated_event(Event_Id{ 0 });

	action.add_indistinguishability_relation(Agent_Id{ 0 }, Event_Id{ 0 }, Event_Id{ 0 });
	action.add_indistinguishability_relation(Agent_Id{ 1 }, Event_Id{ 0 }, Event_Id{ 0 });
	library.add_action(action);
}

void add_actions(Action_Library& library, size_t amount_of_agents) {
	//add_announce_action(library, "in(red,Box0)", amount_of_agents);
	add_announce_action(library, "in(red,Box1)", amount_of_agents);
	//add_announce_action(library, "in(red,Box2)", amount_of_agents);

	//add_pickup_action(library, "in(red,Box0)", "in(red,L)", amount_of_agents);
	add_pickup_action(library, "in(red,Box1)", "in(red,L)", amount_of_agents);
	//add_pickup_action(library, "in(red,Box2)", "in(red, L)", amount_of_agents);
}


State get_initial_state(size_t amount_of_agents) {
	// Agents 0:L  1:Pepper

	State state(amount_of_agents);
	state.create_world();
	state.create_world();
	state.create_world();
	state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
	state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
	state.add_true_propositions(World_Id{ 2 }, { "in(red,Box2)" });
	for (size_t i = 0; i < 3; i++) {
		for (size_t j = 0; j < 3; j++) {
			state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
		}
	}

	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });

	state.add_designated_world(World_Id{ 1 });

	return state;
}

int main(int argc, char* argv[]) {
	using namespace del;

	//size_t amount_of_agents = 2;




	//Formula goal = get_goal_formula();
	//State state = get_initial_state(amount_of_agents);
	//	Action_Library library(amount_of_agents);
	//add_actions(library, amount_of_agents);

	//Domain domain(amount_of_agents);
	
	
	//Planner planner;
	//auto policy = planner.find_policy(goal, library, state);




	//std::cout << policy.to_string() << std::endl;


	DEL_Interface del_interface;
	del_interface.create_policy();
	//Interface_DTO dto = del_interface.get_next_action();
	//del_interface.perform_action(dto.get_action());
	//dto = del_interface.get_next_action();
	//del_interface.perform_action(dto.get_action());

	while (!del_interface.is_solved()) {
		Interface_DTO dto = del_interface.get_next_action();
		if (dto.has_action()) {
			del_interface.perform_action(dto.get_action());
		} else {
			std::cerr << "NO APPLIABLE ACTION" << std::endl;
		}
		if (dto.get_announce_string() != "") {
			std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
		}

	}



	return 0;
}

