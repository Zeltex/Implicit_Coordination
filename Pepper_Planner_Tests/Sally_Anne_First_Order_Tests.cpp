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

			auto in_basket = di->prop("in", "basket", "marble");

			Formula f;
			f.f_prop(in_basket);
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_In)
		{
			prepare_sally_anne();

			size_t agent_S = di->agent("S").id;
			auto in_basket = di->prop("in", "basket", "marble");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_basket));
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_0_False_In)
		{
			prepare_sally_anne();

			auto in_box = di->prop("in", "box", "marble");

			Formula f;
			f.f_prop(in_box);
			Assert::IsFalse(di->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_False_In)
		{
			prepare_sally_anne();

			size_t agent_S = di->agent("S").id;
			auto in_box = di->prop("in", "box", "marble");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_box));
			Assert::IsFalse(di->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_0_Present)
		{
			prepare_sally_anne();

			auto in_basket = di->prop("present", "S");

			Formula f;
			f.f_prop(in_basket);
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_InitialState_Depth_1_Present)
		{
			prepare_sally_anne();

			size_t agent_S = di->agent("S").id;
			auto in_basket = di->prop("present", "A");

			Formula f;
			f.f_believes(agent_S, f.f_prop(in_basket));
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_Action_0)
		{
			prepare_sally_anne();
			auto present_a = di->prop("present", "A");

			Formula f;
			auto formula_id = f.f_prop(present_a);
			Assert::IsTrue(di->query(f));

			di->perform_action("leave", { "A" });

			f.f_not(formula_id);
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_Action_1)
		{
			prepare_sally_anne();
			auto agent_a = di->agent("A").id;
			auto agent_s = di->agent("S").id;
			auto present_a = di->prop("present", "A");
			auto in_basket = di->prop("in", "basket", "marble");
			auto in_box = di->prop("in", "box", "marble");
			tp->print_state();
			di->perform_action("leave", { "A" });

			Formula f0;
			f0.f_believes(agent_a, f0.f_prop(in_basket));

			// A believes marble in basket
			Assert::IsTrue(di->query(f0));

			tp->print_state();
			di->perform_action("move", { "basket", "box", "marble", "S"});

			// A believes marble in basket
			Assert::IsTrue(di->query(f0));

			Formula f1;
			f1.f_believes(agent_s, f1.f_prop(in_box));

			// S believes marble in box
			Assert::IsTrue(di->query(f0));

			Formula f2;
			f2.f_believes(agent_s, f2.f_believes(agent_a, f2.f_prop(in_basket)));

			// S believes A believe marble in basket
			Assert::IsTrue(di->query(f2));

			Formula f3;
			f3.f_prop(in_box);

			// marble in box
			Assert::IsTrue(di->query(f3));
		}

	private:

		Test_Preparer* tp;
		DEL_Interface* di;

		void prepare_sally_anne()
		{
			tp = new Test_Preparer("Sally_Anne_First_Order.maepl");
			di = tp->del_interface;
		}
	};
}