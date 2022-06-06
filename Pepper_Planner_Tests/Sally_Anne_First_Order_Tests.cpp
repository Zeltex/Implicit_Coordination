#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Sally_Anne_First_Order_Tests)
	{
	public:
		TEST_METHOD(Test_InitialState_Depth_0_In)
		{
			prepare_sally_anne();

			auto in_basket = tp->prop("in", "basket", "marble");

			Formula f;
			f.f_prop(in_basket);
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_In)
		{
			prepare_sally_anne();

			size_t agent_S = tp->agent("S").id;
			auto in_basket = tp->prop("in", "basket", "marble");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_basket));
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_0_False_In)
		{
			prepare_sally_anne();

			auto in_box = tp->prop("in", "box", "marble");

			Formula f;
			f.f_prop(in_box);
			Assert::IsFalse(tp->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_False_In)
		{
			prepare_sally_anne();

			size_t agent_S = tp->agent("S").id;
			auto in_box = tp->prop("in", "box", "marble");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_box));
			Assert::IsFalse(tp->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_0_Present)
		{
			prepare_sally_anne();

			auto in_basket = tp->prop("present", "S");

			Formula f;
			f.f_prop(in_basket);
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_Present)
		{
			prepare_sally_anne();

			size_t agent_S = tp->agent("S").id;
			auto in_basket = tp->prop("present", "A");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_basket));
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_Action_0)
		{
			prepare_sally_anne();
			auto present_a = tp->prop("present", "A");

			Formula f;
			auto formula_id = f.f_prop(present_a);
			Assert::IsTrue(tp->query(f));

			tp->perform("leave", { "A" });

			f.f_not(formula_id);
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_Action_1)
		{
			prepare_sally_anne();
			auto agent_a = tp->agent("A").id;
			auto agent_s = tp->agent("S").id;
			auto present_a = tp->prop("present", "A");
			auto in_basket = tp->prop("in", "basket", "marble");
			auto in_box = tp->prop("in", "box", "marble");

			tp->perform("leave", { "A" });

			Formula f0;
			f0.f_believes(agent_a, f0.f_prop(in_basket));

			// A believes marble in basket
			Assert::IsTrue(tp->query(f0));

			tp->perform("move", { "basket", "box", "marble", "S"});

			// A believes marble in basket
			Assert::IsTrue(tp->query(f0));

			Formula f1;
			f1.f_believes(agent_s, f1.f_prop(in_box));

			// S believes marble in box
			Assert::IsTrue(tp->query(f0));

			Formula f2;
			f2.f_believes(agent_s, f2.f_believes(agent_a, f2.f_prop(in_basket)));

			// S believes A believe marble in basket
			Assert::IsTrue(tp->query(f2));

			Formula f3;
			f3.f_prop(in_box);

			// marble in box
			Assert::IsTrue(tp->query(f3));
		}

	private:

		Test_Preparer* tp;

		void prepare_sally_anne()
		{
			tp = new Test_Preparer("Sally_Anne_First_Order.maepl");
		}
	};
}