#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/Formula.hpp"
#include "../Pepper_Planner/Formula_Component.hpp"
#include "../Pepper_Planner/State.hpp"
#include "../Pepper_Planner/Action.hpp"
#include "../Pepper_Planner/Action_Event.hpp"
#include "../Pepper_Planner/DEL_Operations.hpp"
#include "../Pepper_Planner/Types.hpp"
#include "../Pepper_Planner/DEL_Operations.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(DEL_Operations_Tests)
	{
	public:

		TEST_METHOD(Perspective_Shift_Agent_P) {
			//Agents; 0:Pepper, 1:L
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

			Agent agent(Agent_Id{ 0 });
			auto new_state = perform_perspective_shift(state, agent);


			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 1 }, worlds.size());
			Assert::AreEqual(size_t{ 1 }, new_state.get_indistinguishability_relations(Agent_Id{ 0 }).size());
			Assert::AreEqual(size_t{ 1 }, new_state.get_indistinguishability_relations(Agent_Id{ 1 }).size());

			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 0 }, World_Id{ 0 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 0 }, World_Id{ 0 }));
		}

		TEST_METHOD(Perspective_Shift_Agent_L) {
			//Agents; 0:Pepper, 1:L
			State state(2);
			state.create_world();
			state.create_world();
			state.create_world();
			state.create_world();
			state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
			state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
			state.add_true_propositions(World_Id{ 2 }, { "in(red,Box1)" });
			state.add_true_propositions(World_Id{ 3 }, { "in(red,Box2)" });

			state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 1 });

			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 0 });
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 2 });
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 3 });

			for (size_t i : {0, 2, 3}) {
				for (size_t j : {0, 2, 3}) {
					state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ j });
					state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
				}
			}


			state.add_designated_world(World_Id{ 1 });

			Agent agent(Agent_Id{ 1 });
			auto new_state = perform_perspective_shift(state, agent);


			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 4 }, worlds.size());
			Assert::AreEqual(size_t{ 10 }, new_state.get_indistinguishability_relations(Agent_Id{ 0 }).size());
			Assert::AreEqual(size_t{ 13 }, new_state.get_indistinguishability_relations(Agent_Id{ 1 }).size());

			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 1 }));

			Assert::AreEqual(size_t{ 4 }, new_state.get_designated_worlds_count());
		}
	};
}