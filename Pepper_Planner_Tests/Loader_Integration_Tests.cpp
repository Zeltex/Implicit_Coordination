
#include "CppUnitTest.h"

#include <iostream>
#include <fstream>

#define EXPORT_TEST_FUNCTIONS
#include "Custom_Lexer.hpp"
#include "Custom_Parser.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"

#include "Proposition_Instance_Buffer.cpp"
#include "General_World.cpp"
//#include "Atom_Arguments.cpp"

#include <Loader.hpp>

//#include "Loader.hpp"
//#include "Domain.hpp"

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
			Proposition goal_id = propositions_lookup->get(Proposition_Instance{ *atom_lookup, "goal", "a0", "c0" });

			Formula f;
			f.f_prop(goal_id);
			Assert::IsTrue(del_interface->query(f));
		}


		TEST_METHOD(Test_Goal_Depth_1)
		{
			prepare_example_1();
			Proposition goal_c0 = propositions_lookup->get(Proposition_Instance{ *atom_lookup, "goal", "a0", "c0" });
			Proposition goal_x1 = propositions_lookup->get(Proposition_Instance{ *atom_lookup, "goal", "a0", "x1" });

			Formula f;
			f.f_believes(0, f.f_or({ f.f_prop(goal_c0), f.f_prop(goal_x1) }));
			Assert::IsTrue(del_interface->query(f));
		}

		TEST_METHOD(Test_Goal_Depth_1_False)
		{
			prepare_example_1();
			size_t agent_1 = agent_lookup->get("a1").get_id().id;
			Proposition goal_c1 = propositions_lookup->get(Proposition_Instance{ *atom_lookup, "goal", "a0", "c1" });
			Proposition goal_c2 = propositions_lookup->get(Proposition_Instance{ *atom_lookup, "goal", "a0", "c2" });

			Formula f;
			Formula_Id incorrect_formula = f.f_or({f.f_believes(agent_1, f.f_prop(goal_c1)), f.f_believes(agent_1, f.f_prop(goal_c2) )});
			Assert::IsFalse(del_interface->query(f));

			Formula_Id correct_formula = f.f_not(incorrect_formula);
			Assert::IsTrue(del_interface->query(f));
		}

	private:

		void prepare_example_1()
		{
			del_interface = new DEL_Interface(test_folder_path + "Example_1.maepl");
			propositions_lookup = &del_interface->get_propositions_lookup();
			atom_lookup = &del_interface->get_atom_lookup();
			agent_lookup = &del_interface->get_agent_lookup();
		}

		DEL_Interface* del_interface;
		const Propositions_Lookup* propositions_lookup;
		const Atom_Lookup* atom_lookup;
		const Agents* agent_lookup;

		std::string test_folder_path = "../../Test_Cases/";
	};
}