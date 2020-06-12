#include "Graph.hpp"
#include <iostream>

int main(int argc, char* argv[]) {

	del::Graph graph;
	del::State state1;
	del::State state2;
	del::State state3;
	del::State state4;
	del::Node_Id node1 = graph.create_root_node(state1);
	del::Node_Id node2 = graph.create_node(state2, node1);
	del::Node_Id node3 = graph.create_root_node(state3);
	del::Node_Id node4 = graph.create_node(state4, node3);

	std::cout << node1.id << "\n";

	graph.add_to_frontier(node1);
	graph.add_to_frontier(node2);

	return 0;
}