#include "Graph.hpp"
#include "Formula.hpp"
#include <iostream>
#include <chrono>
#include <ctime>    
#include <time.h>


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
#include "Domain_Interface_Implementation.h"
#include "Loader.hpp"

using namespace del;

void find_and_execute_policy() {


	auto time1 = std::chrono::high_resolution_clock::now();

	DEL_Interface del_interface("../examples/simple.maepl");
	//DEL_Interface del_interface("../examples/simple_transfer.maepl");
	//DEL_Interface del_interface("../examples/Second_Order.maepl");
	//del_interface.print_current_state_to_graph("../State_Before.dot");
//del_interface.perform_action("perceive", "L", { "box1", "red_cube" });
//del_interface.print_current_state_to_graph("../State_After.dot");

	auto time2 = std::chrono::high_resolution_clock::now();
	del_interface.create_policy();
	// Some computation here
	auto time3 = std::chrono::high_resolution_clock::now();

	auto elapsed1 = time2 - time1;
	auto elapsed2 = time3 - time2;

	

	std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
	std::cout << "planning execution time " << (elapsed2.count() / 1000000) << "ms\n";

	while (!del_interface.is_solved()) {
		Interface_DTO dto = del_interface.get_next_action();
		if (dto.has_action()) {

			del_interface.perform_action(dto.get_action());
		}
		else {
			std::cerr << "NO APPLIABLE ACTION" << std::endl;
			break;
		}
		if (dto.get_announce_string() != "") {
			std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
		}

	}
}

void execute_test_case() {
	DEL_Interface del_interface("../examples/Sally_Anne.maepl");

	del_interface.perform_action("put", "S", { "S", "basket", "marble" });
	del_interface.perform_oc("S", {  }, { {"perceives", "S", "A"}, {"perceives", "A", "S"} });
	del_interface.perform_action("pickup", "A", { "basket", "A", "marble" });
	del_interface.perform_action("put", "A", { "A", "box", "marble" });

}

void execute_second_order() {
	DEL_Interface del_interface("../examples/Second_Order.maepl");
	del_interface.perform_oc("A", {  }, { {"perceives", "A", "B"}, {"perceives", "A", "C"}, {"perceives", "B", "A"}, {"perceives", "C", "A"} });
	del_interface.perform_action("transfer", "B", { "box1", "box2", "cube_red" });
	del_interface.perform_oc("B", {  }, { {"perceives", "B", "C"}, {"perceives", "C", "B"} });
	del_interface.perform_action("transfer", "C", { "box2", "box1", "cube_red" });
	del_interface.perform_oc("A", { {"perceives", "A", "C"}, {"perceives", "C", "A"} }, {  });
	del_interface.perform_action("transfer", "A", { "box1", "box2", "cube_red" });
	del_interface.perform_oc("A", {  }, { {"perceives", "A", "C"}, {"perceives", "C", "A"} });

	Formula goal;
	auto& context = del_interface.get_formula_context();

	auto prop = goal.f_prop({ "in", { "box1", "cube_red" }, context });
	auto belief1 = goal.f_believes(0, prop);
	auto belief2 = goal.f_believes(1, belief1);
	if (del_interface.query(goal)) {
		std::cout << "-=-=- Success -=-=-";
	} else {
		std::cout << "-=-=- Fail -=-=-";
	}
}

void execute_second_order_seeing_is_believing() {

}

int main(int argc, char* argv[]) {
	execute_second_order();
	//execute_test_case();


	//find_and_execute_policy();


	return 0;
}

