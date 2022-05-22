#pragma once

#include <queue>

#include "Node.hpp"
#include "Types.hpp"

namespace del {

	class Agent;
	class Node_Comparator;
	class Graph {
	public:

		Graph() : root(), frontier(), nodes(std::vector<Node>()) {};
		Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent& planning_agent);


		Node_Id get_next_from_frontier();
		bool is_frontier_empty() const;
		void add_to_frontier(const Node& node);
		void add_to_frontier(Node_Id node_id);
		void set_parent_child(const Node& parent_id, Node_Id child, const Action& action);
		void set_parent_child(Node_Id parent_id, Node_Id child_id, const Action& action);
		void set_parent_child(Node_Id parent_id, Node_Id child_id);
		Node& create_and_node(State state, Node_Id parent, Action action_from_parent);
		Node& create_or_node(State state, const Node& parent);
		Node& create_or_node(State state, Node_Id parent);
		Node& create_root_node(State state);

		// The reference returned may become invalid if a new node is created 
		// since the vector may reallocate memory on the heap
		std::vector<Node>& get_nodes();
		const std::vector<Node>& get_const_nodes() const;
		Node& get_node(Node_Id node_id);
		const Node& get_node(Node_Id node_id) const;
		const Node& get_const_node(Node_Id node_id) const;
		Node& get_root_node();

		std::string to_string(const Domain& domain) const;
	private:
		Node_Id root;
		std::priority_queue < Node_Entry, std::vector<Node_Entry>, Node_Entry_Comparator> frontier;
		std::vector<Node> nodes;
	};
}