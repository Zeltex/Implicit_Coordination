#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "Formula.hpp"
#include "Formula_Component.hpp"

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
			f.f_prop( {"first",{"a"}});
			Assert::IsTrue(f.valuate({ {"first",{"a"}} }));
		}

		TEST_METHOD(Prop_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_prop( {"first",{"a"}});
			Assert::IsFalse(f.valuate({  {"second",{"a"}} }));
		}

		TEST_METHOD(Not_Valuation_Prop_Exists) {
			Formula f;
			f.f_not(f.f_prop( {"first",{"a"}}));
			Assert::IsFalse(f.valuate({ {"first",{"a"}} }));
		}

		TEST_METHOD(Not_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_not(f.f_prop( {"first",{"a"}}));
			Assert::IsTrue(f.valuate({ {"second",{"a"}} }));
		}

		TEST_METHOD(And_Valuation_Prop_Exists) {
			Formula f;
			f.f_and({ f.f_prop( {"first",{"a"}}) , f.f_prop( {"second",{"a"}})});
			Assert::IsTrue(f.valuate({ {"first",{"a"}} , {"second",{"a"}} }));
		}

		TEST_METHOD(And_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_and({ f.f_prop( {"first",{"a"}}) , f.f_prop( {"second",{"a"}}) });
			Assert::IsFalse(f.valuate({ {"second",{"a"}} }));
		}

		TEST_METHOD(Or_Valuation_First_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop( {"first",{"a"}}) , f.f_prop( {"second",{"a"}}) });
			Assert::IsTrue(f.valuate({ {"first",{"a"}} }));
		}

		TEST_METHOD(Or_Valuation_Second_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop( {"first",{"a"}}) , f.f_prop( {"second",{"a"}}) });
			Assert::IsTrue(f.valuate({ {"second",{"a"}} }));
		}

		TEST_METHOD(OR_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_or({ f.f_prop( {"first",{"a"}}) , f.f_prop( {"second",{"a"}}) });
			Assert::IsFalse(f.valuate({ {"third",{"a"}} }));
		}

		TEST_METHOD(Big_Formula1) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first",{"a"}}), f.f_prop( {"second",{"a"}}) }), f.f_prop( {"third",{"a"}}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth",{"a"}}), f.f_prop( {"fifth",{"a"}}), f.f_prop( {"sixth",{"a"}}) }) });
			f.f_and({ component1, component2 });
			Assert::IsFalse(f.valuate({ {"first",{"a"}}, {"second",{"a"}}, {"third",{"a"}}, {"fourth",{"a"}}, {"fifth",{"a"}}, {"sixth",{"a"}} }));
		}

		TEST_METHOD(Big_Formula2) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first",{"a"}}), f.f_prop( {"second",{"a"}}) }), f.f_prop( {"third",{"a"}}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop({"fourth",{"a"}}), f.f_prop({"fifth",{"a"}}), f.f_prop({"sixth",{"a"}}) }) });
			f.f_and({ component1, component2 });
			Assert::IsTrue(f.valuate({ {"second",{"a"}}, {"third",{"a"}}, {"fourth",{"a"}}, {"fifth",{"a"}} }));
		}

		TEST_METHOD(Big_Formula3) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first",{"a"}}), f.f_prop( {"second",{"a"}}) }), f.f_prop( {"third",{"a"}}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth",{"a"}}), f.f_prop( {"fifth",{"a"}}), f.f_prop( {"sixth",{"a"}}) }) });
			f.f_and({ component1, component2 });
			Assert::IsFalse(f.valuate({ {"first",{"a"}}, {"second",{"a"}}, {"fourth",{"a"}}, {"fifth",{"a"}} }));
		}

		TEST_METHOD(Big_Formula4) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first",{"a"}}), f.f_prop( {"second",{"a"}}) }), f.f_prop( {"third",{"a"}}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth",{"a"}}), f.f_prop( {"fifth",{"a"}}), f.f_prop( {"sixth",{"a"}}) }) });
			f.f_and({ component1, component2 });
			Assert::IsTrue(f.valuate({ {"second",{"a"}}, {"third",{"a"}} }));
		}


	};
}
