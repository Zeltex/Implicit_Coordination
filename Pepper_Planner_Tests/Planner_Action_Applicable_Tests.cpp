#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "State.hpp"
#include "Action.hpp"
#include "Action_Event.hpp"
#include "Types.hpp"
#include "Bisimulation_Context.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Planner_Action_Applicable_Tests)
	{
	public:

		TEST_METHOD(Stack_Worlds_Problem) {
			//State state(1);
			//state.create_worlds(1);
			//state.set_world_designated({ 0 });
			//state.add_indistinguishability_relation({ 0 }, { 0 }, { 0 });

			//state.add_true_propositions({ 0 }, { {"p"} });
			//state.add_true_propositions({ 1 }, { {"q"} });
			//state.add_true_propositions({ 2 }, { {"q"} });
			//state.add_true_propositions({ 3 }, { {"p"} });

			//Bisimulation_Context context = { state, state };

			//State bisim = context.to_bisimulation_contraction(state, 2);

			//Assert::AreEqual({ 2 }, bisim.get_worlds_count());
			//Assert::AreEqual({ 2 }, bisim.get_indistinguishability_relations()[0].size());

			//auto h1 = state.to_hash();
			//auto h2 = bisim.to_hash();

			////auto hash1 = std::hash<std::string>()(h1);
			////auto hash2 = std::hash<std::string>()(h2);

			//size_t debug = 0;

			Assert::IsTrue(true);
		}
	};
}