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
		Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent& planning_agent);


		NodeOr* get_next_from_frontier();
		bool is_frontier_empty() const;
		void add_to_frontier(NodeOr* node);
		NodeAnd* create_and_node(State state, NodeOr* parent, const Action* action_from_parent);
		NodeOr* create_or_node(NodeAnd* parent, const std::set<World_Id>& designated_worlds);
		NodeAnd* create_root_node(const State& state);

		std::vector<NodeBase*>& get_nodes();
		const std::vector<NodeBase*>& get_const_nodes() const;
		NodeAnd* get_root_node();

		std::string to_string(const Domain& domain) const;
	private:
		NodeAnd* root;
		std::priority_queue<NodeOr*, std::vector<NodeOr*>, Node_Cost_Comparator> frontier;
		std::vector<NodeBase*> nodes;
	};
}