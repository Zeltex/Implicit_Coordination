#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Sally_Anne_Second_Order_Planner_Tests)
	{
	public:
		TEST_METHOD(Test_Goal_Reached)
		{
			prepare_sally_anne();
			bool result = di->create_policy("S");
			Assert::IsTrue(result);
			tp->print_state();

			while (!di->is_solved())
			{
				auto next_action = di->get_next_action();
				Assert::IsTrue(next_action.has_value());
				di->perform_action(next_action.value());

				tp->print_action(next_action.value());
				tp->print_state();
			}

			Assert::IsTrue(di->is_solved());
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