#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Loader_Integration_Test)
	{
	public:
		TEST_METHOD(Test_Goal_Depth_0)
		{
			prepare_example_1();
			const Proposition_Instance* goal_id = di->prop("goal", "a0", "c0" );

			Formula f;
			f.f_prop(goal_id);
			Assert::IsTrue(di->query(f));
		}


		TEST_METHOD(Test_Goal_Depth_1)
		{
			prepare_example_1();
			const Agent* agent_0 = di->agent("a0");
			const Proposition_Instance* goal_c0 = di->prop("goal", "a0", "c0" );
			const Proposition_Instance* goal_x1 = di->prop("goal", "a0", "x1" );

			Formula f;
			f.f_believes(agent_0, f.f_or(f.f_prop(goal_c0), f.f_prop(goal_x1)));
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_Goal_Depth_1_False)
		{
			prepare_example_1();
			const Agent* agent_1 = di->agent("a1");
			const Proposition_Instance* goal_c1 = di->prop("goal", "a0", "c1" );
			const Proposition_Instance* goal_c2 = di->prop("goal", "a0", "c2" );

			Formula f;
			Formula_Component* incorrect_formula = f.f_or(f.f_believes(agent_1, f.f_prop(goal_c1)), f.f_believes(agent_1, f.f_prop(goal_c2)));
			Assert::IsFalse(di->query(f));

			Formula_Component* correct_formula = f.f_not(incorrect_formula);
			Assert::IsTrue(di->query(f));
		}

		TEST_METHOD(Test_Goal_Depth_2)
		{
			prepare_example_1();
			const Agent* agent_0 = di->agent("a0");
			const Proposition_Instance* goal_c0 = di->prop("goal", "a0", "c0");
			const Proposition_Instance* goal_x1 = di->prop("goal", "a0", "x1");

			Formula f;
			f.f_believes(agent_0, f.f_or(f.f_prop(goal_c0), f.f_prop(goal_x1)));
			Assert::IsTrue(di->query(f));
		}

	private:

		Test_Preparer* tp;
		DEL_Interface* di;

		void prepare_example_1()
		{
			tp = new Test_Preparer("Example_1.maepl");
			di = tp->del_interface;
		}
	};
}