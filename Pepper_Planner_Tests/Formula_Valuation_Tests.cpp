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
		Input(std::unordered_map<size_t, std::unordered_set<Proposition>> propositions) : propositions(propositions) {}
		bool valuate_prop(const Proposition& prop, const size_t world_id) const { 
			auto& prop_list = propositions.at(world_id);

			return std::find(prop_list.begin(), prop_list.end(), prop) != prop_list.end(); 
		
		}
		virtual std::set<size_t> get_reachable_worlds(const Proposition& agent_id, size_t world_id) const 
		{ 
			return{};
			//return std::set<size_t>(worlds.at(world_id)); 
		}
		std::unordered_map<size_t, std::unordered_set<Proposition>> propositions;
		std::unordered_map<size_t, std::vector<size_t>> worlds;
	};

	Input get_input() {
		std::unordered_map<size_t, std::unordered_set<Proposition>> propositions;
		propositions[0] = { { 0 } };
		Input input(propositions);
		return std::move(input);
	}

	Input get_input(std::unordered_set<Proposition>&& props) {
		std::unordered_map<size_t, std::unordered_set<Proposition>> propositions;
		propositions[0] = props;
		Input input(propositions);
		return std::move(input);
	}

	TEST_CLASS(Formula_Valuation_Tests)
	{
	public:
		// TODO - Update tests
		//TEST_METHOD(Top_Valuation) {
		//	Formula f;
		//	f.f_top();
		//	auto input = get_input();
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Bot_Valuation) {
		//	Formula f;
		//	f.f_bot();
		//	auto input = get_input();
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Prop_Valuation_Prop_Exists) {
		//	Formula f;
		//	f.f_prop( { 0 });
		//	auto input = get_input();
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Prop_Valuation_Prop_Does_Not_Exist) {
		//	Formula f;
		//	f.f_prop( { 1 });
		//	auto input = get_input();
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Not_Valuation_Prop_Exists) {
		//	Formula f;
		//	f.f_not(f.f_prop( {0}));
		//	auto input = get_input();
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Not_Valuation_Prop_Does_Not_Exist) {
		//	Formula f;
		//	f.f_not(f.f_prop( {1}));
		//	auto input = get_input();
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(And_Valuation_Prop_Exists) {
		//	Formula f;
		//	f.f_and({ f.f_prop( {0}) , f.f_prop( {1})});
		//	auto input = get_input({ {0} , {1} });
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(And_Valuation_Prop_Does_Not_Exist) {
		//	Formula f;
		//	f.f_and({ f.f_prop( {0}) , f.f_prop( {1}) });
		//	auto input = get_input({ {1} });
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Or_Valuation_First_Prop_Exists) {
		//	Formula f;
		//	f.f_or({ f.f_prop( {0}) , f.f_prop( {1}) });
		//	auto input = get_input({ {0} });
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Or_Valuation_Second_Prop_Exists) {
		//	Formula f;
		//	f.f_or({ f.f_prop( {0}) , f.f_prop( {1}) });
		//	auto input = get_input({ {1} });
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(OR_Valuation_Prop_Does_Not_Exist) {
		//	Formula f;
		//	f.f_or({ f.f_prop( {0}) , f.f_prop( {1}) });
		//	auto input = get_input({ {2} });
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Big_Formula1) {
		//	Formula f;
		//	auto component1 = f.f_and({ f.f_or({ f.f_prop( {0}), f.f_prop( {1}) }), f.f_prop( {2}) });
		//	auto component2 = f.f_not({ f.f_and({ f.f_prop( {3}), f.f_prop( {4}), f.f_prop( {5}) }) });
		//	f.f_and({ component1, component2 });
		//	auto input = get_input({ {0}, {1}, {2}, {3}, {4}, {5} });
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Big_Formula2) {
		//	Formula f;
		//	auto component1 = f.f_and({ f.f_or({ f.f_prop( {0}), f.f_prop( {1}) }), f.f_prop( {2}) });
		//	auto component2 = f.f_not({ f.f_and({ f.f_prop({3}), f.f_prop({4}), f.f_prop({5}) }) });
		//	f.f_and({ component1, component2 });
		//	auto input = get_input({ {1}, {2}, {3}, {4} });
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Big_Formula3) {
		//	Formula f;
		//	auto component1 = f.f_and({ f.f_or({ f.f_prop( {0}), f.f_prop( {1}) }), f.f_prop( {2}) });
		//	auto component2 = f.f_not({ f.f_and({ f.f_prop( {3}), f.f_prop( {4}), f.f_prop( {5}) }) });
		//	f.f_and({ component1, component2 });
		//	auto input = get_input({ {0}, {1}, {3}, {4} });
		//	Assert::IsFalse(f.valuate(0, domain, state));
		//}

		//TEST_METHOD(Big_Formula4) {
		//	Formula f;
		//	auto component1 = f.f_and({ f.f_or({ f.f_prop( {0}), f.f_prop( {1}) }), f.f_prop( {2}) });
		//	auto component2 = f.f_not({ f.f_and({ f.f_prop( {3}), f.f_prop( {4}), f.f_prop( {5}) }) });
		//	f.f_and({ component1, component2 });
		//	auto input = get_input({ {1}, {2} });
		//	Assert::IsTrue(f.valuate(0, domain, state));
		//}

		// TODO - Test Belief
	};
}
