#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/World.hpp"
#include "../Formula/Formula.hpp"
#include "../Formula/Formula_Component.hpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(World_Valuation_Tests)
	{
	public:

		TEST_METHOD(Valuate_Positive_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ {"first", { "a" } } });
			Formula f;
			f.f_prop( "first(a)" );
			Assert::IsTrue(world.valuate(f));
		}

		TEST_METHOD(Valuate_Never_Added_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ {"first", { "a" } } });
			Formula f;
			f.f_prop( "second(a)" );
			Assert::IsFalse(world.valuate(f));
		}

		TEST_METHOD(Valuate_Deleted_Positive_Proposition) {
			World world(World_Id{ 0 });
			world.add_true_propositions({ {"first", {"a"} } });
			world.remove_true_propositions({ {"first", {"a"} } });
			Formula f;
			f.f_prop( "first(a)" );
			Assert::IsFalse(world.valuate(f));
		}

	};
}
