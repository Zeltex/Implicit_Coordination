#pragma once

#include <queue>

#include "Node.hpp"
#include "Types.hpp"

namespace del {

	class Graph {
	public:

		Graph() : frontier(), nodes(std::vector<Node>()) {};
		Graph(size_t node_size) { nodes.reserve(node_size); };
		Graph(size_t node_size, const State& state) { nodes.reserve(node_size); add_to_frontier(create_root_node(state)); };


		Node_Id get_next_from_frontier();
		bool is_frontier_empty() const;
		void add_to_frontier(Node_Id node_id);
		void set_parent_child(Node_Id parent_id, Node_Id child_id, const Action& action);
		void set_parent_child(Node_Id parent_id, Node_Id child_id);
		Node_Id create_and_node(State state, Node_Id parent, Action action_from_parent);
		Node_Id create_or_node(State state, Node_Id parent);
		Node_Id create_root_node(State state);

		// The reference returned may become invalid if a new node is created 
		// since the vector may reallocate memory on the heap
		std::vector<Node>& get_nodes();
		const std::vector<Node>& get_const_nodes() const;
		Node& get_node(Node_Id node_id);
		const Node& get_const_node(Node_Id node_id) const;
		Node& get_root_node();

		std::string to_string(const Domain& domain) const;
		std::string to_graph(const Domain& domain) const;
		std::string to_graph_simple(const Domain& domain) const;
		std::string to_partial_graph(const Domain& domain) const;
	private:
		Node_Id root;
		std::priority_queue < Node_Entry, std::vector<Node_Entry>, Node_Entry_Comparator> frontier;
		std::vector<Node> nodes;
	};
}