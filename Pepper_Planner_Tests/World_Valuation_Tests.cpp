#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/World.hpp"
#include "../Pepper_Planner/Formula_Creator.hpp"
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
			World world;
			world.add_true_proposition("first");
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("first"));
			Assert::IsTrue(world.valuate(formula));
		}

		TEST_METHOD(Valuate_Never_Added_Proposition) {
			World world;
			world.add_true_proposition("first");
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("second"));
			Assert::IsFalse(world.valuate(formula));
		}

		TEST_METHOD(Valuate_Deleted_Positive_Proposition) {
			World world;
			world.add_true_proposition("first");
			world.remove_true_proposition("first");
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("first"));
			Assert::IsFalse(world.valuate(formula));
		}

	};
}
