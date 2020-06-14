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

		TEST_METHOD(Product_Update_Test_One_Event_Applicable_In_One_Designated_World) {
			
			State state(2);
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

			Action action(Agent_Id{ 1 }, 2);
			Formula f;
			f.f_prop("in(red,Box1)");
			Event_Id id{ 0 };

			Action_Event event = Action_Event(id, std::move(f), std::unordered_set<std::string>(), std::unordered_set<std::string>());
			action.add_event(event);
			State& new_state = perform_product_update(state, action);
			
			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 1 }, worlds.size());

			auto& propositions = worlds[0].get_true_propositions();
			Assert::AreEqual(size_t{ 1 }, propositions.size());
			
			Assert::IsTrue(propositions.find("in(red,Box1)") != propositions.end());

		}

		TEST_METHOD(Product_Update_Test_Perceive_Action_Only_Observable_To_Owner) {
			//Agents; 0:Pepper, 1:L
			State state(2);
			state.create_world();
			state.create_world();
			state.create_world();
			state.add_true_propositions(World_Id{ 0 }, { "in(red,Box0)" });
			state.add_true_propositions(World_Id{ 1 }, { "in(red,Box1)" });
			state.add_true_propositions(World_Id{ 2 }, { "in(red,Box2)" });
			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
					state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ j });
				}
			}

			state.add_designated_world(World_Id{ 0 });
			state.add_designated_world(World_Id{ 1 });
			state.add_designated_world(World_Id{ 2 });

			Action action(Agent_Id{ 1 }, 2);
			Formula f;
			f.f_prop("in(red,Box1)");
			Event_Id id{ 0 };

			Action_Event event = Action_Event(id, std::move(f), std::unordered_set<std::string>(), std::unordered_set<std::string>());
			action.add_event(event);

			Formula f2;
			f2.f_top();
			Event_Id id2{ 1 };
			Action_Event event2 = Action_Event(id2, std::move(f2), std::unordered_set<std::string>(), std::unordered_set<std::string>());
			action.add_event(event2);

			action.add_indistinguishability_relation(Agent_Id{ 1 }, id, id2);
			action.add_indistinguishability_relation(Agent_Id{ 1 }, id, id);
			action.add_indistinguishability_relation(Agent_Id{ 1 }, id2, id2);
			action.add_indistinguishability_relation(Agent_Id{ 0 }, id, id);
			action.add_indistinguishability_relation(Agent_Id{ 0 }, id2, id2);
			action.add_designated_event(id);


			State& new_state = perform_product_update(state, action);

			// Correct amount of worlds
			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 4 }, worlds.size());

			// Correct designated world
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 0 }));
			Assert::IsTrue(new_state.is_world_designated(World_Id{ 1 }));
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 2 }));
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 3 }));

			// Designated world has correct proposition
			auto& propositions = worlds[1].get_true_propositions();
			Assert::AreEqual(size_t{ 1 }, propositions.size());
			Assert::IsTrue(propositions.find("in(red,Box1)") != propositions.end());

			// Correct agent 0 (pepper) indistinguishability
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 0 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 1 }));
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 2 }));
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 3 }));

			// Correct agent 1 (L) indistinguishability
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 0 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 2 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 3 }));


		}
	};
}