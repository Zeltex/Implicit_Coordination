#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>
#include <algorithm>

#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "State.hpp"
#include "Action.hpp"
#include "Action_Event.hpp"
#include "DEL_Operations.hpp"
#include "Types.hpp"
#include "DEL_Operations.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(DEL_Operations_Tests)
	{
	public:

		TEST_METHOD(Product_Update_Test_One_Event_Applicable_In_One_Designated_World) {
			

			std::unordered_map<std::string, Atom_Id> atom_to_id;
			atom_to_id["red"] = 0;
			atom_to_id["Box0"] = 1;
			atom_to_id["Box1"] = 2;
			atom_to_id["Box2"] = 3;

			State state(2);
			state.create_world();
			state.create_world();
			state.create_world();

			state.add_true_propositions(World_Id{ 0 }, { {"in", {atom_to_id["red"], atom_to_id["Box0"]} } });
			state.add_true_propositions(World_Id{ 1 }, { {"in", {atom_to_id["red"], atom_to_id["Box1"]} } });
			state.add_true_propositions(World_Id{ 2 }, { {"in", {atom_to_id["red"], atom_to_id["Box2"]} } });
			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
				}
			}

			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 });

			state.add_designated_world(World_Id{ 1 });

			Action action(Agent_Id{ 1 }, 2);
			Formula f;
			f.f_prop({ "in", { atom_to_id["red"], atom_to_id["Box1"] } });
			Action_Event event = Action_Event(Event_Id{ 0 }, std::move(f), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
			action.add_event(event);
			State& new_state = perform_product_update(state, action, { {{0}, {atom_to_id.size()}, "Pepper"}, {{1}, {atom_to_id.size()+1}, "L"} });
			
			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 1 }, worlds.size());

			auto& propositions = worlds[0].get_true_propositions();
			Assert::AreEqual(size_t{ 1 }, propositions.size());
			
			Proposition_Instance proposition_to_find = { "in",{atom_to_id["red"], atom_to_id["Box1"]} };
			Assert::IsTrue(std::find(propositions.begin(), propositions.end(), proposition_to_find) != propositions.end());

		}

		TEST_METHOD(Product_Update_Test_Perceive_Action_Only_Observable_To_Owner) {


			std::unordered_map<std::string, Atom_Id> atom_to_id;
			atom_to_id["red"] = 0;
			atom_to_id["Box0"] = 1;
			atom_to_id["Box1"] = 2;
			atom_to_id["Box2"] = 3;

			//Agents; 0:Pepper, 1:L
			State state(2);
			state.create_world();
			state.create_world();
			state.create_world();
			state.add_true_propositions(World_Id{ 0 }, { {"in", {atom_to_id["red"], atom_to_id["Box0"]} } });
			state.add_true_propositions(World_Id{ 1 }, { {"in", {atom_to_id["red"], atom_to_id["Box1"]} } });
			state.add_true_propositions(World_Id{ 2 }, { {"in", {atom_to_id["red"], atom_to_id["Box2"]} } });
			for (size_t i = 0; i < 3; i++) {
				for (size_t j = 0; j < 3; j++) {
					state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ j });
					state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ j });
				}
			}

			state.add_designated_world(World_Id{ 0 });
			state.add_designated_world(World_Id{ 1 });
			state.add_designated_world(World_Id{ 2 });

			Action action(Agent_Id{ 1 }, 2);
			Formula f;
			f.f_prop({ "in", { atom_to_id["red"],atom_to_id["Box1"] } });
			Event_Id id{ 0 };

			Action_Event event = Action_Event(id, std::move(f), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
			action.add_event(event);

			Formula f2;
			f2.f_top();
			Event_Id id2{ 1 };
			Action_Event event2 = Action_Event(id2, std::move(f2), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
			action.add_event(event2);

			action.add_reachability(Agent_Id{ 1 }, id, id2, Formula());
			action.add_reachability(Agent_Id{ 1 }, id, id, Formula());
			action.add_reachability(Agent_Id{ 1 }, id2, id2, Formula());
			action.add_reachability(Agent_Id{ 0 }, id, id, Formula());
			action.add_reachability(Agent_Id{ 0 }, id2, id2, Formula());
			action.add_designated_event(id);

			State& new_state = perform_product_update(state, action, { {{0}, {atom_to_id.size()}, "Pepper"}, {{1}, {atom_to_id.size()+1}, "L"} });

			// Correct amount of worlds
			auto& worlds = new_state.get_worlds();
			Assert::AreEqual(size_t{ 4 }, worlds.size());

			// Correct designated world
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 0 }));
			Assert::IsTrue(new_state.is_world_designated(World_Id{ 1 }));
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 2 }));
			Assert::IsFalse(new_state.is_world_designated(World_Id{ 3 }));

			// Designated world has correct proposition
			auto& propositions = worlds[1].get_true_propositions();
			Assert::AreEqual(size_t{ 1 }, propositions.size());
			Proposition_Instance proposition_to_find = { "in", {atom_to_id["red"], atom_to_id["Box1"]} };
			Assert::IsTrue(std::find(propositions.begin(), propositions.end(), proposition_to_find) != propositions.end());

			// Correct agent 0 (pepper) indistinguishability
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 0 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 1 }));
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 2 }));
			Assert::IsFalse(new_state.is_one_reachable(Agent_Id{ 0 }, World_Id{ 1 }, World_Id{ 3 }));

			// Correct agent 1 (L) indistinguishability
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 0 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 1 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 2 }));
			Assert::IsTrue(new_state.is_one_reachable(Agent_Id{ 1 }, World_Id{ 1 }, World_Id{ 3 }));
		}

		TEST_METHOD(Product_Update_Test_Perceive_Two_Events) {

			std::unordered_map<std::string, Atom_Id> atom_to_id;
			atom_to_id["red"] = 0;
			atom_to_id["Box0"] = 1;
			atom_to_id["Box1"] = 2;
			atom_to_id["Box2"] = 3;

			//Agents; 0:Pepper, 1:L
			State state(2);
			state.create_world();
			state.create_world();
			state.create_world();
			state.add_true_propositions(World_Id{ 0 }, { {"in", {atom_to_id["red"], atom_to_id["Box1"]} } });
			state.add_true_propositions(World_Id{ 1 }, { {"in", {atom_to_id["red"], atom_to_id["Box0"]} } });
			state.add_true_propositions(World_Id{ 2 }, { {"in", {atom_to_id["red"], atom_to_id["Box2"]} } });
			for (size_t i = 0; i < 3; i++) {
					state.add_indistinguishability_relation(Agent_Id{ 0 }, World_Id{ i }, World_Id{ i });
					state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ i }, World_Id{ i });
			}
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 0 }, World_Id{ 2 });
			state.add_indistinguishability_relation(Agent_Id{ 1 }, World_Id{ 2 }, World_Id{ 0 });

			state.add_designated_world(World_Id{ 0 });

			Action action(Agent_Id{ 1 }, 2);
			Formula f;
			f.f_prop({ "in", { atom_to_id["red"],atom_to_id["Box2"] } });
			Event_Id id{ 0 };
			Action_Event event = Action_Event(id, std::move(f), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
			action.add_event(event);

			Formula f2;
			f2.f_not(f2.f_prop({ "in", { atom_to_id["red"],atom_to_id["Box2"] } }));
			Event_Id id2{ 1 };
			Action_Event event2 = Action_Event(id2, std::move(f2), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
			action.add_event(event2);

			action.add_reachability(Agent_Id{ 1 }, id, id, Formula());
			action.add_reachability(Agent_Id{ 1 }, id2, id2, Formula());
			action.add_reachability(Agent_Id{ 0 }, id, id, Formula());
			action.add_reachability(Agent_Id{ 0 }, id2, id2, Formula());
			action.add_designated_event(id);
			action.add_designated_event(id2);


			State& new_state = perform_product_update(state, action, { {{0}, {atom_to_id.size()}, "Pepper"}, {{1}, {atom_to_id.size()+1}, "L"} });

			// TODO
		}
	};
}