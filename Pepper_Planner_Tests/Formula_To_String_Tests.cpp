#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "Types.hpp"
#include "Formula.hpp"
#include "Formula_Component.hpp"

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
			Assert::AreEqual(f.to_string({}), std::string("TOP"));
		}

		TEST_METHOD(Bot_String) {
			Formula f;
			f.f_bot();
			Assert::AreEqual(f.to_string({}), std::string("BOT"));
		}

		TEST_METHOD(Prop_String) {
			Formula f;
			f.f_prop({0});
			Assert::AreEqual(f.to_string({}), std::string("0()"));
		}

		TEST_METHOD(Not_String) {
			Formula f;
			f.f_not(f.f_prop({0}));
			Assert::AreEqual(f.to_string({}), std::string("Not(0())"));
		}

		TEST_METHOD(And_String) {
			Formula f;
			f.f_and({ f.f_not(f.f_prop({0})), f.f_prop({1}) });
			Assert::AreEqual(f.to_string({}), std::string("And(Not(0());1())"));
		}

		TEST_METHOD(Or_String) {
			Formula f;
			f.f_or({ f.f_and({f.f_prop({0}), f.f_prop({1})}), f.f_prop({2}) });
			Assert::AreEqual(f.to_string({}), std::string("Or(And(0();1());third())"));
		}

		TEST_METHOD(Believes_String) {
			Formula f;
			f.f_believes( 9 , f.f_and({ f.f_prop({0}), f.f_prop({1})}));
			Assert::AreEqual(f.to_string({}), std::string("Believes_9(And(0();1()))"));
		}

		TEST_METHOD(Everyone_Believes_String) {
			Formula f;
			f.f_everyone_Believes(f.f_and({ f.f_prop({0}), f.f_prop({1}) }));
			Assert::AreEqual(f.to_string({}), std::string("Everyone_Believes(And(0();1()))"));
		}

		TEST_METHOD(Common_Knowledge_String) {
			Formula f;
			f.f_common_Knowledge(f.f_and({ f.f_prop({0}), f.f_prop({1}) }));
			Assert::AreEqual(f.to_string({}), std::string("Common_Knowledge(And(0();1()))"));
		}
	};
}
