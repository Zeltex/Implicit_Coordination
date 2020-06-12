#pragma once

#include <queue>

#include "Node.hpp"
#include "Types.hpp"

namespace del {

	class Graph {
	public:

		Graph(): frontier(), nodes(std::vector<Node>()) {};


		Node_Id get_next_from_frontier();
		bool is_frontier_empty();
		void add_to_frontier(Node_Id node_id);
		Node_Id create_node(State state, Node_Id parent);
		Node_Id create_root_node(State state);

		// The reference returned may become invalid if a new node is created 
		// since the vector may reallocate memory on the heap
		Node& get_node(Node_Id node_id);
	private:
		std::deque<int> frontier;
		std::vector<Node> nodes;
	};
}