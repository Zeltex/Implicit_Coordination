#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/World.hpp"
#include "../Pepper_Planner/Formula.hpp"
#include "../Pepper_Planner/Formula_Component.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(World_Valuation_Tests)
	{
	public:

		TEST_METHOD(Valuate_Positive_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ "first" });
			Formula f;
			f.f_prop("first");
			Assert::IsTrue(world.valuate(f));
		}

		TEST_METHOD(Valuate_Never_Added_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ "first" });
			Formula f;
			f.f_prop("second");
			Assert::IsFalse(world.valuate(f));
		}

		TEST_METHOD(Valuate_Deleted_Positive_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ "first" });
			world.remove_true_propositions({ "first" });
			Formula f;
			f.f_prop("first");
			Assert::IsFalse(world.valuate(f));
		}

	};
}
