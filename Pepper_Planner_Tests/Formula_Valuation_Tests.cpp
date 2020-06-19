#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Formula/Formula.hpp"
#include "../Formula/Formula_Component.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Formula_Valuation_Tests)
	{
	public:

		TEST_METHOD(Top_Valuation) {
			Formula f;
			f.f_top();
			Assert::IsTrue(f.valuate({}));
		}

		TEST_METHOD(Bot_Valuation) {
			Formula f;
			f.f_bot();
			Assert::IsFalse(f.valuate({}));
		}

		TEST_METHOD(Prop_Valuation_Prop_Exists) {
			Formula f;
			f.f_prop("first");
			Assert::IsTrue(f.valuate({"first"}));
		}

		TEST_METHOD(Prop_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_prop("first");
			Assert::IsFalse(f.valuate({ "second" }));
		}

		TEST_METHOD(Not_Valuation_Prop_Exists) {
			Formula f;
			f.f_not(f.f_prop("first"));
			Assert::IsFalse(f.valuate({ "first" }));
		}

		TEST_METHOD(Not_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_not(f.f_prop("first"));
			Assert::IsTrue(f.valuate({ "second" }));
		}

		TEST_METHOD(And_Valuation_Prop_Exists) {
			Formula f;
			f.f_and({ f.f_prop("first") , f.f_prop("second")});
			Assert::IsTrue(f.valuate({ "first", "second" }));
		}

		TEST_METHOD(And_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_and({ f.f_prop("first") , f.f_prop("second") });
			Assert::IsFalse(f.valuate({ "second" }));
		}

		TEST_METHOD(Or_Valuation_First_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop("first") , f.f_prop("second") });
			Assert::IsTrue(f.valuate({ "first" }));
		}

		TEST_METHOD(Or_Valuation_Second_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop("first") , f.f_prop("second") });
			Assert::IsTrue(f.valuate({ "second" }));
		}

		TEST_METHOD(OR_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_or({ f.f_prop("first") , f.f_prop("second") });
			Assert::IsFalse(f.valuate({ "third" }));
		}

		TEST_METHOD(Big_Formula1) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop("first"), f.f_prop("second") }), f.f_prop("third") });
			auto component2 = f.f_not({ f.f_and({ f.f_prop("fourth"), f.f_prop("fifth"), f.f_prop("sixth") }) });
			f.f_and({ component1, component2 });
			Assert::IsFalse(f.valuate({ "first", "second", "third", "fourth", "fifth", "sixth" }));
		}

		TEST_METHOD(Big_Formula2) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop("first"), f.f_prop("second") }), f.f_prop("third") });
			auto component2 = f.f_not({ f.f_and({ f.f_prop("fourth"), f.f_prop("fifth"), f.f_prop("sixth") }) });
			f.f_and({ component1, component2 });
			Assert::IsTrue(f.valuate({ "second", "third", "fourth", "fifth" }));
		}

		TEST_METHOD(Big_Formula3) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop("first"), f.f_prop("second") }), f.f_prop("third") });
			auto component2 = f.f_not({ f.f_and({ f.f_prop("fourth"), f.f_prop("fifth"), f.f_prop("sixth") }) });
			f.f_and({ component1, component2 });
			Assert::IsFalse(f.valuate({ "first", "second", "fourth", "fifth" }));
		}

		TEST_METHOD(Big_Formula4) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop("first"), f.f_prop("second") }), f.f_prop("third") });
			auto component2 = f.f_not({ f.f_and({ f.f_prop("fourth"), f.f_prop("fifth"), f.f_prop("sixth") }) });
			f.f_and({ component1, component2 });
			Assert::IsTrue(f.valuate({ "second", "third" }));
		}


	};
}
