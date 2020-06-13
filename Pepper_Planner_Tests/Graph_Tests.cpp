#include "pch.h"
#include "CppUnitTest.h"

#include <iostream>

#include "../Pepper_Planner/Graph.hpp"
#include "../Pepper_Planner/Node.hpp"
#include "../Pepper_Planner/State.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace PepperPlannerTests
{
	using namespace del;
	TEST_CLASS(Graph_Tests)
	{
	public:

		TEST_METHOD(Frontier_Is_Popped_Correctly) {

			Graph graph;
			State state1;
			State state2;
			Node_Id node1 = graph.create_root_node(state1);
			Node_Id node2 = graph.create_node(state2, node1);

			graph.add_to_frontier(node1);
			graph.add_to_frontier(node2);

			Node_Id node_returned1 = graph.get_next_from_frontier();
			Node_Id node_returned2 = graph.get_next_from_frontier();

			Assert::AreEqual(node1.id, node_returned1.id);
			Assert::AreEqual(node2.id, node_returned2.id);
		}

		TEST_METHOD(Node_Parent_Is_Set_Correctly) {
			Graph graph;
			State state1;
			State state2;
			Node_Id node1 = graph.create_root_node(state1);
			Node_Id node2 = graph.create_node(state2, node1);

			Assert::AreEqual(graph.get_node(node2).get_parent().id, node1.id);
		}

		TEST_METHOD(Node_Child_Is_Set_Correctly) {
			Graph graph;
			State state1;
			State state2;
			Node_Id node1 = graph.create_root_node(state1);
			Node_Id node2 = graph.create_node(state2, node1);
			auto children = graph.get_node(node1).get_children();
			Assert::IsTrue(std::find(children.begin(), children.end(), node2) != children.end());
		}

		TEST_METHOD(Root_Is_Set_Correctly) {
			Graph graph;
			State state1;
			State state2;
			Node_Id node1 = graph.create_root_node(state1);
			Node_Id node2 = graph.create_node(state2, node1);
			Assert::IsTrue(graph.get_node(node1).is_root_node());
			Assert::IsFalse(graph.get_node(node2).is_root_node());
		}
	};
}
