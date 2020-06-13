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
	TEST_CLASS(Formula_To_String_Tests)
	{
	public:

		TEST_METHOD(Top_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_top());
			Assert::AreEqual(formula.to_string(), std::string("TOP"));
		}

		TEST_METHOD(Bot_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_bot());
			Assert::AreEqual(formula.to_string(), std::string("BOT"));
		}

		TEST_METHOD(Prop_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_prop("Inner"));
			Assert::AreEqual(formula.to_string(), std::string("Inner"));
		}

		TEST_METHOD(Not_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_not(fc.f_prop("Inner")));
			Assert::AreEqual(formula.to_string(), std::string("Not(Inner)"));
		}

		TEST_METHOD(And_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_and({ fc.f_not(fc.f_prop("Inner")), fc.f_prop("Second Inner") }));
			Assert::AreEqual(formula.to_string(), std::string("And(Not(Inner);Second Inner)"));
		}

		TEST_METHOD(Or_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_or({ fc.f_and({fc.f_prop("first"), fc.f_prop("second")}), fc.f_prop("third") }));
			Assert::AreEqual(formula.to_string(), std::string("Or(And(first;second);third)"));
		}

		TEST_METHOD(Believes_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_believes(Agent_Id{ 9 }, fc.f_and({ fc.f_prop("first"), fc.f_prop("second")})));
			Assert::AreEqual(formula.to_string(), std::string("Believes_9(And(first;second))"));
		}

		TEST_METHOD(Everyone_Believes_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_everyone_Believes(fc.f_and({ fc.f_prop("first"), fc.f_prop("second") })));
			Assert::AreEqual(formula.to_string(), std::string("Everyone_Believes(And(first;second))"));
		}

		TEST_METHOD(Common_Knowledge_String) {
			Formula_Creator fc;
			auto formula = Formula(fc.f_common_Knowledge(fc.f_and({ fc.f_prop("first"), fc.f_prop("second") })));
			Assert::AreEqual(formula.to_string(), std::string("Common_Knowledge(And(first;second))"));
		}
	};
}
