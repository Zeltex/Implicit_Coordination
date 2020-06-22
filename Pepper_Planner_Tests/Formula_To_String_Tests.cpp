#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/Types.hpp"
#include "../Formula/Formula.hpp"
#include "../Formula/Formula_Component.hpp"

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
			f.f_prop({"first",{"a"}});
			Assert::AreEqual(f.to_string(), std::string("first(a)"));
		}

		TEST_METHOD(Not_String) {
			Formula f;
			f.f_not(f.f_prop({"first",{"a"}}));
			Assert::AreEqual(f.to_string(), std::string("Not(first(a))"));
		}

		TEST_METHOD(And_String) {
			Formula f;
			f.f_and({ f.f_not(f.f_prop({"first",{"a"}})), f.f_prop({"second",{"a"}}) });
			Assert::AreEqual(f.to_string(), std::string("And(Not(first(a));second(a))"));
		}

		TEST_METHOD(Or_String) {
			Formula f;
			f.f_or({ f.f_and({f.f_prop({"first",{"a"}}), f.f_prop({"second",{"a"}})}), f.f_prop({"third", {"a"}}) });
			Assert::AreEqual(f.to_string(), std::string("Or(And(first(a);second(a));third(a))"));
		}

		TEST_METHOD(Believes_String) {
			Formula f;
			f.f_believes( 9 , f.f_and({ f.f_prop({"first",{"a"}}), f.f_prop({"second",{"a"}})}));
			Assert::AreEqual(f.to_string(), std::string("Believes_9(And(first(a);second(a)))"));
		}

		TEST_METHOD(Everyone_Believes_String) {
			Formula f;
			f.f_everyone_Believes(f.f_and({ f.f_prop({"first",{"a"}}), f.f_prop({"second",{"a"}}) }));
			Assert::AreEqual(f.to_string(), std::string("Everyone_Believes(And(first(a);second(a)))"));
		}

		TEST_METHOD(Common_Knowledge_String) {
			Formula f;
			f.f_common_Knowledge(f.f_and({ f.f_prop({"first",{"a"}}), f.f_prop({"second",{"a"}}) }));
			Assert::AreEqual(f.to_string(), std::string("Common_Knowledge(And(first(a);second(a)))"));
		}
	};
}
