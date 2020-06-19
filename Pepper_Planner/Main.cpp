#include "Graph.hpp"
#include "../Formula/Formula.hpp"
#include <iostream>

#include "World.hpp"
#include "../Formula/Formula.hpp"
#include "../Formula/Formula_Component.hpp"
#include "Action.hpp"
#include "Action_Event.hpp"
#include "DEL_Operations.hpp"
#include "Action_Library.hpp"
#include "Planner.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"
#include "Domain_Interface_Implementation.h"
#include "../Domain_Loader/Loader.hpp"

using namespace del;


Formula get_goal_formula() {

	Formula f;
	f.f_prop("in(red,L)");
	return std::move(f);
}

int main(int argc, char* argv[]) {
	using namespace del;

	////size_t amount_of_agents = 2;




	////Formula goal = get_goal_formula();
	////State state = get_initial_state(amount_of_agents);
	////	Action_Library library(amount_of_agents);
	////add_actions(library, amount_of_agents);

	////Domain domain(amount_of_agents);
	//
	//
	////Planner planner;
	////auto policy = planner.find_policy(goal, library, state);




	////std::cout << policy.to_string() << std::endl;

	//auto goal = get_goal_formula();

	//DEL_Interface del_interface(0);
	//del_interface.create_policy(goal);
	////Interface_DTO dto = del_interface.get_next_action();
	////del_interface.perform_action(dto.get_action());
	////dto = del_interface.get_next_action();
	////del_interface.perform_action(dto.get_action());

	//while (!del_interface.is_solved()) {
	//	Interface_DTO dto = del_interface.get_next_action();
	//	if (dto.has_action()) {
	//		del_interface.perform_action(dto.get_action());
	//	} else {
	//		std::cerr << "NO APPLIABLE ACTION" << std::endl;
	//	}
	//	if (dto.get_announce_string() != "") {
	//		std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
	//	}

	//}

	Domain_Interface_Implementation domain;
	Loader loader;
	loader.parse(&domain, "../examples/in.snazzle");


	return 0;
}

