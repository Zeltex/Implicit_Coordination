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
		Node_Id create_and_node(State state, Node_Id parent, Action action_from_parent);
		Node_Id create_or_node(State state, Node_Id parent);
		Node_Id create_root_node(State state);

		// The reference returned may become invalid if a new node is created 
		// since the vector may reallocate memory on the heap
		Node& get_node(Node_Id node_id);
		Node& get_root_node();

		std::string to_string(const Domain& domain) const;
		std::string to_graph(const Domain& domain) const;
		std::string to_partial_graph(const Domain& domain) const;
	private:
		Node_Id root;
		// TODO - Change to Node_Id
		std::deque<int> frontier;
		std::vector<Node> nodes;
	};
}