#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Test_MAPF_Planner)
	{
	public:
		TEST_METHOD(Test_P1)
		{
			perform("p1.maepl");
		}

		TEST_METHOD(Test_P2)
		{
			perform("p2.maepl");
		}
		TEST_METHOD(Test_P3)
		{
			perform("p3.maepl");
		}
		TEST_METHOD(Test_P4)
		{
			perform("p4.maepl");
		}

	private:

		Test_Preparer* tp;
		DEL_Interface* di;

		void perform(std::string fileName)
		{
			tp = new Test_Preparer(fileName);
			di = tp->del_interface;
			bool result = di->create_policy("a0");
			Assert::IsTrue(result);
			tp->print_policy();
			tp->execute_until_solved();
		}

		void prepare(std::string fileName)
		{
			tp = new Test_Preparer(fileName);
			di = tp->del_interface;
		}
	};
}