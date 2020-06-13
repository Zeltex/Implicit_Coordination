#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/Formula.hpp"
#include "../Pepper_Planner/Formula_Component.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Formula_To_String_Tests)
	{
	public:

		TEST_METHOD(Top_String) {
			Formula f;
			f.f_top();
			Assert::AreEqual(f.to_string(), std::string("TOP"));
		}

		TEST_METHOD(Bot_String) {
			Formula f;
			f.f_bot();
			Assert::AreEqual(f.to_string(), std::string("BOT"));
		}

		TEST_METHOD(Prop_String) {
			Formula f;
			f.f_prop("Inner");
			Assert::AreEqual(f.to_string(), std::string("Inner"));
		}

		TEST_METHOD(Not_String) {
			Formula f;
			f.f_not(f.f_prop("Inner"));
			Assert::AreEqual(f.to_string(), std::string("Not(Inner)"));
		}

		TEST_METHOD(And_String) {
			Formula f;
			f.f_and({ f.f_not(f.f_prop("Inner")), f.f_prop("Second Inner") });
			Assert::AreEqual(f.to_string(), std::string("And(Not(Inner);Second Inner)"));
		}

		TEST_METHOD(Or_String) {
			Formula f;
			f.f_or({ f.f_and({f.f_prop("first"), f.f_prop("second")}), f.f_prop("third") });
			Assert::AreEqual(f.to_string(), std::string("Or(And(first;second);third)"));
		}

		TEST_METHOD(Believes_String) {
			Formula f;
			f.f_believes(Agent_Id{ 9 }, f.f_and({ f.f_prop("first"), f.f_prop("second")}));
			Assert::AreEqual(f.to_string(), std::string("Believes_9(And(first;second))"));
		}

		TEST_METHOD(Everyone_Believes_String) {
			Formula f;
			f.f_everyone_Believes(f.f_and({ f.f_prop("first"), f.f_prop("second") }));
			Assert::AreEqual(f.to_string(), std::string("Everyone_Believes(And(first;second))"));
		}

		TEST_METHOD(Common_Knowledge_String) {
			Formula f;
			f.f_common_Knowledge(f.f_and({ f.f_prop("first"), f.f_prop("second") }));
			Assert::AreEqual(f.to_string(), std::string("Common_Knowledge(And(first;second))"));
		}
	};
}
