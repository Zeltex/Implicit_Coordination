#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "Types.hpp"
#include "DEL_Operations.hpp"
#include "Bisimulation_Context.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Bisimulation_Context_Tests)
	{
	public:

		TEST_METHOD(Test_Scenario_From_Gumenuks_Thesis_Positive) {
			State state1(1);
			state1.create_worlds(8);

			state1.add_true_propositions(World_Id{ 0 }, {   });
			state1.add_true_propositions(World_Id{ 1 }, { {1}});
			state1.add_true_propositions(World_Id{ 2 }, { {0} });
			state1.add_true_propositions(World_Id{ 3 }, { {0}, {1} });
			state1.add_true_propositions(World_Id{ 4 }, {   });
			state1.add_true_propositions(World_Id{ 5 }, { {1} });
			state1.add_true_propositions(World_Id{ 6 }, { {0} });
			state1.add_true_propositions(World_Id{ 7 }, { {0}, {1} });

			for (size_t i = 1; i < 8; i++) {
				state1.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 0 }, World_Id{ i });
				state1.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
			}

			state1.set_world_designated(World_Id{ 0 });
			state1.set_world_designated(World_Id{ 3 });
			state1.set_world_designated(World_Id{ 4 });
			state1.set_world_designated(World_Id{ 7 });

			State state2(1);
			state2.create_worlds(5);
			state2.add_true_propositions(World_Id{ 0 }, {});
			state2.add_true_propositions(World_Id{ 1 }, {});
			state2.add_true_propositions(World_Id{ 2 }, { {1} });
			state2.add_true_propositions(World_Id{ 3 }, { {0} });
			state2.add_true_propositions(World_Id{ 4 }, { {0}, {1} });

			for (size_t i = 1; i < 5; i++) {
				state2.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 0 }, World_Id{ i });
				state2.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
			}

			state2.set_world_designated(World_Id{ 0 });
			state2.set_world_designated(World_Id{ 1 });
			state2.set_world_designated(World_Id{ 4 });

			Assert::IsTrue(are_states_bisimilar(state1, state2));

		}

		TEST_METHOD(Test_Scenario_From_Gumenuks_Thesis_Negative) {
			State state1(1);
			state1.create_worlds(8);

			state1.add_true_propositions(World_Id{ 0 }, {   });
			state1.add_true_propositions(World_Id{ 1 }, { {1} });
			state1.add_true_propositions(World_Id{ 2 }, { {0} });
			state1.add_true_propositions(World_Id{ 3 }, { {0}, {1} });
			state1.add_true_propositions(World_Id{ 4 }, {   });
			state1.add_true_propositions(World_Id{ 5 }, { {1} });
			state1.add_true_propositions(World_Id{ 6 }, { {0} });
			state1.add_true_propositions(World_Id{ 7 }, { {0}, {1} });

			for (size_t i = 1; i < 8; i++) {
				state1.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 0 }, World_Id{ i });
				state1.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
			}

			state1.set_world_designated(World_Id{ 0 });
			state1.set_world_designated(World_Id{ 3 });
			state1.set_world_designated(World_Id{ 4 });
			state1.set_world_designated(World_Id{ 5 });
			state1.set_world_designated(World_Id{ 7 });

			State state2(1);
			state2.create_worlds(5);
			state2.add_true_propositions(World_Id{ 0 }, {});
			state2.add_true_propositions(World_Id{ 1 }, {});
			state2.add_true_propositions(World_Id{ 2 }, { {1} });
			state2.add_true_propositions(World_Id{ 3 }, { {0} });
			state2.add_true_propositions(World_Id{ 4 }, { {0}, {1} });

			for (size_t i = 1; i < 5; i++) {
				state2.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ 0 }, World_Id{ i });
				state2.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
			}

			state2.set_world_designated(World_Id{ 0 });
			state2.set_world_designated(World_Id{ 1 });
			state2.set_world_designated(World_Id{ 4 });

			Assert::IsFalse(are_states_bisimilar(state1, state2));
		}
	};
}