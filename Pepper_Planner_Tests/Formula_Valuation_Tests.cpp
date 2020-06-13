#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/Formula.hpp"
#include "../Pepper_Planner/Formula_Component.hpp"
#include "../Pepper_Planner/Formula_Creator.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Formula_Valuation_Tests)
	{
	public:

		TEST_METHOD(Top_Valuation) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_top());
			Assert::IsTrue(formula.valuate({}));
		}

		TEST_METHOD(Bot_Valuation) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_bot());
			Assert::IsFalse(formula.valuate({}));
		}

		TEST_METHOD(Prop_Valuation_Prop_Exists) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("first"));
			Assert::IsTrue(formula.valuate({"first"}));
		}

		TEST_METHOD(Prop_Valuation_Prop_Does_Not_Exist) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("first"));
			Assert::IsFalse(formula.valuate({ "second" }));
		}

		TEST_METHOD(Not_Valuation_Prop_Exists) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_not(fc.f_prop("first")));
			Assert::IsFalse(formula.valuate({ "first" }));
		}

		TEST_METHOD(Not_Valuation_Prop_Does_Not_Exist) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_not(fc.f_prop("first")));
			Assert::IsTrue(formula.valuate({ "second" }));
		}

		TEST_METHOD(And_Valuation_Prop_Exists) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_and({ fc.f_prop("first") , fc.f_prop("second")}));
			Assert::IsTrue(formula.valuate({ "first", "second" }));
		}

		TEST_METHOD(And_Valuation_Prop_Does_Not_Exist) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_and({ fc.f_prop("first") , fc.f_prop("second") }));
			Assert::IsFalse(formula.valuate({ "second" }));
		}

		TEST_METHOD(Or_Valuation_First_Prop_Exists) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_or({ fc.f_prop("first") , fc.f_prop("second") }));
			Assert::IsTrue(formula.valuate({ "first" }));
		}

		TEST_METHOD(Or_Valuation_Second_Prop_Exists) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_or({ fc.f_prop("first") , fc.f_prop("second") }));
			Assert::IsTrue(formula.valuate({ "second" }));
		}

		TEST_METHOD(OR_Valuation_Prop_Does_Not_Exist) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_or({ fc.f_prop("first") , fc.f_prop("second") }));
			Assert::IsFalse(formula.valuate({ "third" }));
		}

		TEST_METHOD(Big_Formula1) {
			Formula_Creator fc;
			auto component1 = fc.f_and({ fc.f_or({ fc.f_prop("first"), fc.f_prop("second") }), fc.f_prop("third") });
			auto component2 = fc.f_not({ fc.f_and({ fc.f_prop("fourth"), fc.f_prop("fifth"), fc.f_prop("sixth") }) });
			auto formula = Formula(fc.f_and({ component1, component2 }));
			Assert::IsFalse(formula.valuate({ "first", "second", "third", "fourth", "fifth", "sixth" }));
		}

		TEST_METHOD(Big_Formula2) {
			Formula_Creator fc;
			auto component1 = fc.f_and({ fc.f_or({ fc.f_prop("first"), fc.f_prop("second") }), fc.f_prop("third") });
			auto component2 = fc.f_not({ fc.f_and({ fc.f_prop("fourth"), fc.f_prop("fifth"), fc.f_prop("sixth") }) });
			auto formula = Formula(fc.f_and({ component1, component2 }));
			Assert::IsTrue(formula.valuate({ "second", "third", "fourth", "fifth" }));
		}

		TEST_METHOD(Big_Formula3) {
			Formula_Creator fc;
			auto component1 = fc.f_and({ fc.f_or({ fc.f_prop("first"), fc.f_prop("second") }), fc.f_prop("third") });
			auto component2 = fc.f_not({ fc.f_and({ fc.f_prop("fourth"), fc.f_prop("fifth"), fc.f_prop("sixth") }) });
			auto formula = Formula(fc.f_and({ component1, component2 }));
			Assert::IsFalse(formula.valuate({ "first", "second", "fourth", "fifth" }));
		}

		TEST_METHOD(Big_Formula4) {
			Formula_Creator fc;
			auto component1 = fc.f_and({ fc.f_or({ fc.f_prop("first"), fc.f_prop("second") }), fc.f_prop("third") });
			auto component2 = fc.f_not({ fc.f_and({ fc.f_prop("fourth"), fc.f_prop("fifth"), fc.f_prop("sixth") }) });
			auto formula = Formula(fc.f_and({ component1, component2 }));
			Assert::IsTrue(formula.valuate({ "second", "third" }));
		}


	};
}
