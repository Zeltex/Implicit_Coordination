#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Sally_Anne_Second_Order_Planner_Tests)
	{
	public:
		//TEST_METHOD(Test_Goal_Reached)
		//{
		//	// It seems it is impossible to find a plan for this
		//	//Assert::IsTrue(false);

		//	prepare_sally_anne();
		//	bool result = di->create_policy("S");
		//	Assert::IsTrue(result);
		//	tp->execute_until_solved();
		//}

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