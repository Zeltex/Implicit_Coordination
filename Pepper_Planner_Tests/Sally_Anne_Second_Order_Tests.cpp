#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Sally_Anne_Second_Order_Tests)
	{
	public:
		TEST_METHOD(Test_Second_Order_False_Belief)
		{
			prepare_sally_anne();

			auto agent_a = di->agent("A").id;
			auto agent_s = di->agent("S").id;
			auto present_a = di->prop("present", "A");
			auto in_basket = di->prop("in", "basket", "marble");
			auto in_box = di->prop("in", "box", "marble");


			di->perform_action("leave", { "A" });
			tp->print_state();

			di->perform_action("peak", { "A" });
			tp->print_state();

			di->perform_action("move", { "basket", "box", "marble", "S" });
			tp->print_state();

			Formula f;
			f.f_believes(agent_a, f.f_believes(agent_s, f.f_believes(agent_a, f.f_prop(in_basket))));

			// Anne believes Sally believes Anne believes the marble is in the basket
			Assert::IsTrue(di->query(f));

			Formula f0;
			f0.f_prop(in_box);

			// Marble is actually in box
			Assert::IsTrue(di->query(f0));
		}

	private:

		Test_Preparer* tp;
		DEL_Interface* di;

		void prepare_sally_anne()
		{
			tp = new Test_Preparer("Sally_Anne_Peak.maepl");
			di = tp->del_interface;
		}
	};
}