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
	f.f_prop({ "in", { "red","L" } });
	return std::move(f);
}

int main(int argc, char* argv[]) {
	using namespace del;


	Domain_Interface_Implementation domain_interface;
	Loader loader;
	loader.parse(&domain_interface, "../examples/in.snazzle");

	std::tuple<Domain, Action_Library> results = domain_interface.get_loaded();

	return 0;
}

