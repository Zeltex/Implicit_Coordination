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

int main(int argc, char* argv[]) {
	using namespace del;

	DEL_Interface del_interface("../examples/simple.maepl");
	del_interface.create_policy();

	while (!del_interface.is_solved()) {
		Interface_DTO dto = del_interface.get_next_action();
		if (dto.has_action()) {
			del_interface.perform_action(dto.get_action());
		}
		else {
			std::cerr << "NO APPLIABLE ACTION" << std::endl;
		}
		if (dto.get_announce_string() != "") {
			std::cout << "ANNOUNCING: " << dto.get_announce_string() << std::endl;
		}

	}

	return 0;
}

