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
int main(int argc, char* argv[]) {
	using namespace del;

	State state(2);
	state.create_world();
	state.create_world();
	state.create_world();
	state.create_world();
	state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
	state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
	state.add_true_propositions(World_Id{ 2 }, { "in(red,Box1)" });
	state.add_true_propositions(World_Id{ 3 }, { "in(red,Box2)" });

	for (size_t i = 0; i < 4; i++) {
		state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
	}

	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 0 });
	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });
	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 2 });
	state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 3 });

	for (size_t i : {0, 2, 3}) {
		for (size_t j : {0, 2, 3}) {
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ j });
		}
	}


	state.add_designated_world(World_Id{ 1 });
	
	std::cout << state.to_string() << "\n";

	return 0;
}

