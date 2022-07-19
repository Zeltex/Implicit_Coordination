#include "CppUnitTest.h"
#include "Test_Preparer.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Accessiblity_Tests)
	{
	public:
		TEST_METHOD(Test_Initial_Accessibility)
		{
			prepare_example_2();
			const State& state = di->get_current_state();

			const Agent* agent = di->agent("a0");
			auto& designated_worlds = state.get_designated_worlds();

			Assert::AreEqual(designated_worlds.size(), (size_t)1);
			auto it = designated_worlds.begin();

			Assert::AreEqual(it->id, (size_t)0);

			auto& reachable_worlds = state.get_reachable_worlds(agent, *it);
			Assert::AreEqual(reachable_worlds.size(), (size_t)3);
			Assert::IsTrue(reachable_worlds.find(3) == reachable_worlds.end());
		}

		TEST_METHOD(Test_Perspective_Shift)
		{
			prepare_example_2();
			State state = di->get_current_state();

			const Agent* agent = di->agent("a0");

			state.shift_and_contract(agent);

			auto& designated_worlds = state.get_designated_worlds();

			Assert::AreEqual(designated_worlds.size(), (size_t)3);
		}

	private:

		Test_Preparer* tp;
		DEL_Interface* di;

		void prepare_example_2()
		{
			tp = new Test_Preparer("Example_2.maepl");
			di = tp->del_interface;
		}
	};
}