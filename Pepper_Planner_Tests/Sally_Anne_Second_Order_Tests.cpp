#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Sally_Anne_Second_Order_Tests)
	{
	public:
		TEST_METHOD(Test_InitialState_Depth_0_In)
		{
			prepare_sally_anne();

			auto agent_a = tp->agent("A").id;
			auto agent_s = tp->agent("S").id;
			auto present_a = tp->prop("present", "A");
			auto in_basket = tp->prop("in", "basket", "marble");
			auto in_box = tp->prop("in", "box", "marble");


			tp->perform("leave", { "A" });
			tp->print_state();

			tp->perform("peak", { "A" });
			tp->print_state();

			tp->perform("move", { "basket", "box", "marble", "S" });
			tp->print_state();

			Formula f;
			f.f_believes(agent_a, f.f_believes(agent_s, f.f_believes(agent_a, f.f_prop(in_basket))));

			// Anne believes Sally believes Anne believes the marble is in the basket
			Assert::IsTrue(tp->query(f));

			Formula f0;
			f0.f_prop(in_box);

			// Marble is actually in box
			Assert::IsTrue(tp->query(f0));
		}

	private:

		Test_Preparer* tp;

		void prepare_sally_anne()
		{
			tp = new Test_Preparer("Sally_Anne_Peak.maepl");
		}
	};
}