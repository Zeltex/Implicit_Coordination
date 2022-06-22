#pragma once

#include <queue>

#include "Node.hpp"
#include "Node_Comparator.hpp"
#include "Types.hpp"

namespace del {

	class Agent;
	class Node_Comparator;
	class State;

	class Graph {
	public:

		Graph();
		Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent& planning_agent);


		Node* get_next_from_frontier();
		bool is_frontier_empty() const;
		void add_to_frontier(Node* node);
		void set_parent_child(Node* parent, Node* child, const Action& action);
		void set_parent_child(Node* parent, Node* child);
		Node* create_and_node(State state, Node* parent, Action action_from_parent);
		Node* create_or_node(State state, Node* parent);
		Node* create_root_node(State state);

		std::vector<Node*>& get_nodes();
		const std::vector<Node*>& get_const_nodes() const;
		Node* get_root_node();

		std::string to_string(const Domain& domain) const;
	private:
		Node* root;
		std::priority_queue < Node*, std::vector<Node*>, Node_Cost_Comparator> frontier;
		std::vector<Node*> nodes;
	};
}