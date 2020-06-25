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

void find_and_execute_policy() {
	DEL_Interface del_interface("../examples/simple.maepl");
	//del_interface.print_current_state_to_graph("../State_Before.dot");
//del_interface.perform_action("perceive", "L", { "box1", "red_cube" });
//del_interface.print_current_state_to_graph("../State_After.dot");

	del_interface.create_policy();

	while (!del_interface.is_solved()) {
		Interface_DTO dto = del_interface.get_next_action();
		if (dto.has_action()) {

			//del_interface.print_current_state_to_graph("../State_Before.dot");
			del_interface.perform_action(dto.get_action());
			//del_interface.print_current_state_to_graph("../State_After.dot");
		}
		else {
			std::cerr << "NO APPLIABLE ACTION" << std::endl;
		}
		if (dto.get_announce_string() != "") {
			std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
		}

	}
}

void execute_test_case() {
	DEL_Interface del_interface("../examples/Sally_Anne.maepl");

	//del_interface.print_current_state_to_graph("../Sally_Anne0.dot");
	del_interface.perform_action("put", "S", { "S", "basket", "marble" });
	//del_interface.print_current_state_to_graph("../Sally_Anne1.dot");
	del_interface.remove_perceivability({ "S" }, { "A" });
	del_interface.remove_perceivability({ "A" }, { "S" });
	del_interface.perform_action("pickup", "A", { "basket", "A", "marble" });
	//del_interface.print_current_state_to_graph("../Sally_Anne2.dot");
	del_interface.perform_action("put", "A", { "A", "box", "marble" });
	//del_interface.print_current_state_to_graph("../Sally_Anne3.dot");

}

int main(int argc, char* argv[]) {
	execute_test_case();


	//find_and_execute_policy(del_interface);


	return 0;
}

