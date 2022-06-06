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
			Proposition goal_id = tp->prop("goal", "a0", "c0" );

			Formula f;
			f.f_prop(goal_id);
			Assert::IsTrue(tp->query(f));
		}


		TEST_METHOD(Test_Goal_Depth_1)
		{
			prepare_example_1();
			size_t agent_0 = tp->agent("a0").id;
			Proposition goal_c0 = tp->prop("goal", "a0", "c0" );
			Proposition goal_x1 = tp->prop("goal", "a0", "x1" );

			Formula f;
			f.f_believes(agent_0, f.f_or({ f.f_prop(goal_c0), f.f_prop(goal_x1) }));
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_Goal_Depth_1_False)
		{
			prepare_example_1();
			size_t agent_1 = tp->agent("a1").id;
			Proposition goal_c1 = tp->prop("goal", "a0", "c1" );
			Proposition goal_c2 = tp->prop("goal", "a0", "c2" );

			Formula f;
			Formula_Id incorrect_formula = f.f_or({f.f_believes(agent_1, f.f_prop(goal_c1)), f.f_believes(agent_1, f.f_prop(goal_c2) )});
			Assert::IsFalse(tp->query(f));

			Formula_Id correct_formula = f.f_not(incorrect_formula);
			Assert::IsTrue(tp->query(f));
		}

		TEST_METHOD(Test_Goal_Depth_2)
		{
			prepare_example_1();
			size_t agent_0 = tp->agent("a0").id;
			Proposition goal_c0 = tp->prop("goal", "a0", "c0");
			Proposition goal_x1 = tp->prop("goal", "a0", "x1");

			Formula f;
			f.f_believes(agent_0, f.f_or({ f.f_prop(goal_c0), f.f_prop(goal_x1) }));
			Assert::IsTrue(tp->query(f));
		}

	private:

		Test_Preparer* tp;

		void prepare_example_1()
		{
			tp = new Test_Preparer("Example_1.maepl");
		}
	};
}