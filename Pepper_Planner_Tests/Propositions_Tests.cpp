#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Propositions_Tests)
	{
	public:
		TEST_METHOD(Test_Order)
		{
			prepare("p1.maepl");

			auto prop0 = di->prop("at", "a1", "c1");
			auto prop1 = di->prop("at", "a0", "c2");
			auto prop2 = di->prop("free", "c0");
			auto prop3 = di->prop("goal", "a1", "c1");
			auto prop4 = di->prop("goal", "a0", "c0");
			auto prop5 = di->prop("free", "x1");

			Propositions props;
			props.insert(prop0);
			props.insert(prop1);
			props.insert(prop2);
			props.insert(prop3);
			props.insert(prop4);
			props.insert(prop5);

			std::string expected = ", at(a0, c2), at(a1, c1), free(c0), free(x1), goal(a0, c0), goal(a1, c1)";
			std::string actual = props.to_string();
			Assert::AreEqual(expected, actual);
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
			tp->execute_until_solved();
		}

		void prepare(std::string fileName)
		{
			tp = new Test_Preparer(fileName);
			di = tp->del_interface;
		}
	};
}