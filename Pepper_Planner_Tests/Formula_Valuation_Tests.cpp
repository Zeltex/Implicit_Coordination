#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "Formula_Input_Interface.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;

	class Input : public Formula_Input_Interface {
	public:
		Input(std::unordered_map<size_t, std::vector<Proposition_Instance>> propositions) : propositions(propositions) {}
		virtual const std::vector<Proposition_Instance>& get_true_propositions(size_t world_id) const { return propositions.at(world_id); }
		virtual std::vector<size_t> get_reachable_worlds(size_t agent_id, size_t world_id) const { return std::vector<size_t>(worlds.at(world_id)); };
		std::unordered_map<size_t, std::vector<Proposition_Instance>> propositions;
		std::unordered_map<size_t, std::vector<size_t>> worlds;
	};

	Input get_input() {
		std::unordered_map<size_t, std::vector<Proposition_Instance>> propositions;
		propositions[0] = { {"first" } };
		Input input(propositions);
		return std::move(input);
	}

	Input get_input(std::vector<Proposition_Instance>&& props) {
		std::unordered_map<size_t, std::vector<Proposition_Instance>> propositions;
		propositions[0] = props;
		Input input(propositions);
		return std::move(input);
	}

	TEST_CLASS(Formula_Valuation_Tests)
	{
	public:

		TEST_METHOD(Top_Valuation) {
			Formula f;
			f.f_top();
			auto input = get_input();
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(Bot_Valuation) {
			Formula f;
			f.f_bot();
			auto input = get_input();
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Prop_Valuation_Prop_Exists) {
			Formula f;
			f.f_prop( {"first"});
			auto input = get_input();
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(Prop_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_prop( {"second"});
			auto input = get_input();
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Not_Valuation_Prop_Exists) {
			Formula f;
			f.f_not(f.f_prop( {"first"}));
			auto input = get_input();
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Not_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_not(f.f_prop( {"second"}));
			auto input = get_input();
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(And_Valuation_Prop_Exists) {
			Formula f;
			f.f_and({ f.f_prop( {"first"}) , f.f_prop( {"second"})});
			auto input = get_input({ {"first"} , {"second"} });
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(And_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_and({ f.f_prop( {"first"}) , f.f_prop( {"second"}) });
			auto input = get_input({ {"second"} });
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Or_Valuation_First_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop( {"first"}) , f.f_prop( {"second"}) });
			auto input = get_input({ {"first"} });
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(Or_Valuation_Second_Prop_Exists) {
			Formula f;
			f.f_or({ f.f_prop( {"first"}) , f.f_prop( {"second"}) });
			auto input = get_input({ {"second"} });
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(OR_Valuation_Prop_Does_Not_Exist) {
			Formula f;
			f.f_or({ f.f_prop( {"first"}) , f.f_prop( {"second"}) });
			auto input = get_input({ {"third"} });
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Big_Formula1) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first"}), f.f_prop( {"second"}) }), f.f_prop( {"third"}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth"}), f.f_prop( {"fifth"}), f.f_prop( {"sixth"}) }) });
			f.f_and({ component1, component2 });
			auto input = get_input({ {"first"}, {"second"}, {"third"}, {"fourth"}, {"fifth"}, {"sixth"} });
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Big_Formula2) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first"}), f.f_prop( {"second"}) }), f.f_prop( {"third"}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop({"fourth"}), f.f_prop({"fifth"}), f.f_prop({"sixth"}) }) });
			f.f_and({ component1, component2 });
			auto input = get_input({ {"second"}, {"third"}, {"fourth"}, {"fifth"} });
			Assert::IsTrue(f.valuate(0, &input));
		}

		TEST_METHOD(Big_Formula3) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first"}), f.f_prop( {"second"}) }), f.f_prop( {"third"}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth"}), f.f_prop( {"fifth"}), f.f_prop( {"sixth"}) }) });
			f.f_and({ component1, component2 });
			auto input = get_input({ {"first"}, {"second"}, {"fourth"}, {"fifth"} });
			Assert::IsFalse(f.valuate(0, &input));
		}

		TEST_METHOD(Big_Formula4) {
			Formula f;
			auto component1 = f.f_and({ f.f_or({ f.f_prop( {"first"}), f.f_prop( {"second"}) }), f.f_prop( {"third"}) });
			auto component2 = f.f_not({ f.f_and({ f.f_prop( {"fourth"}), f.f_prop( {"fifth"}), f.f_prop( {"sixth"}) }) });
			f.f_and({ component1, component2 });
			auto input = get_input({ {"second"}, {"third"} });
			Assert::IsTrue(f.valuate(0, &input));
		}

		// TODO - Test Belief
	};
}
