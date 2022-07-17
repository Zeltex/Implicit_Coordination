#pragma once


#include "Types.hpp"

#include <queue>
#include <set>

namespace del {

	class Action;
	class Agent;
	class Domain;
	class NodeAnd;
	class NodeBase;
	class NodeOr;
	class Node_Comparator;
	class State;

	class Graph {
	public:
		~Graph();
		Graph();
		Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent* planning_agent);


		NodeOr* get_next_from_frontier();
		bool is_frontier_empty() const;
		void add_to_frontier(NodeOr* node);
		NodeAnd* create_and_node(State state, NodeOr* parent, const Action* action_from_parent);
		NodeOr* create_or_node(State state, NodeAnd* parent);
		NodeAnd* create_root_node(const State& state);

		NodeAnd* get_root_node();
		void calculate_value();

		std::string to_string() const;
	private:
		NodeAnd* root;
		std::priority_queue<NodeOr*, std::vector<NodeOr*>, Node_Cost_Comparator> frontier;
		std::vector<NodeBase*> nodes;
	};
}