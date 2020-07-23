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

void execute(DEL_Interface& del_interface) {
	bool failed = false;
	while (!del_interface.is_solved()) {
		Interface_DTO dto = del_interface.get_next_action();
		if (dto.has_action()) {

			del_interface.perform_action(dto.get_action());
			std::cout << "Performed action" << std::endl;
		} else {
			std::cerr << "NO APPLIABLE ACTION" << std::endl;
			std::cout << "-=-=- Fail -=-=-";
			failed = true;
			break;
		}
		if (dto.get_announce_string() != "") {
			std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
		}
	}
	if (!failed) {
		std::cout << "-=-=- Success -=-=-" << std::endl;
	}
}

void false_belief_synthesis() {
	auto time1 = std::chrono::high_resolution_clock::now();

	DEL_Interface del_interface("../examples/False_Belief_Synthesis.maepl");

	auto time2 = std::chrono::high_resolution_clock::now();
	del_interface.create_policy();
	auto time3 = std::chrono::high_resolution_clock::now();

	auto elapsed1 = time2 - time1;
	auto elapsed2 = time3 - time2;



	std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
	std::cout << "planning execution time " << (elapsed2.count() / 1000000) << "ms\n";

	execute(del_interface);
}

void find_and_execute_policy_stack() {


	auto time1 = std::chrono::high_resolution_clock::now();

	DEL_Interface del_interface("../examples/stack.maepl");

	auto time2 = std::chrono::high_resolution_clock::now();
	del_interface.create_policy();
	auto time3 = std::chrono::high_resolution_clock::now();

	auto elapsed1 = time2 - time1;
	auto elapsed2 = time3 - time2;



	std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
	std::cout << "planning execution time " << (elapsed2.count() / 1000000) << "ms\n";

	execute(del_interface);
}

void find_and_execute_policy() {


	auto time1 = std::chrono::high_resolution_clock::now();

	DEL_Interface del_interface("../examples/simple.maepl");
	
	auto time2 = std::chrono::high_resolution_clock::now();
	del_interface.create_policy();
	auto time3 = std::chrono::high_resolution_clock::now();

	auto elapsed1 = time2 - time1;
	auto elapsed2 = time3 - time2;

	

	std::cout << ".maepl load time " << (elapsed1.count() / 1000000) << "ms\n";
	std::cout << "planning execution time " << (elapsed2.count() / 1000000) << "ms\n";


	execute(del_interface);
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
	auto& proposition_context = del_interface.get_proposition_context();
	auto belief_context = del_interface.get_belief_context();

	auto prop = goal.f_prop({ "in", { "box1", "cube_red" }, proposition_context });
	auto belief1 = goal.f_believes("A", prop, belief_context);
	auto belief2 = goal.f_believes("B", belief1, belief_context);
	if (del_interface.query(goal)) {
		std::cout << "-=-=- Success -=-=-";
	} else {
		std::cout << "-=-=- Fail -=-=-";
	}
}

void execute_second_order_seeing_is_believing() {

}

int main(int argc, char* argv[]) {
	//execute_second_order();
	//execute_test_case();


	//find_and_execute_policy();
	//find_and_execute_policy_stack();
	false_belief_synthesis();
	


	return 0;
}

