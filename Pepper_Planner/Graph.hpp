#pragma once

#include <queue>

#include "Node.hpp"
#include "Types.hpp"

namespace del {

	class Graph {
	public:
		Node& get_next_from_frontier();
		bool is_frontier_empty();
		void add_to_frontier(Node_Id node_id);
		void add_parent_child_relation(Node_Id parent, Node_Id child);
		Node& create_node(State state);
	private:
		std::queue<int> frontier;
		std::vector<Node> nodes;
	};
}