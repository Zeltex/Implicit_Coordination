#include "Graph.hpp"

namespace del {
	Node_Id Graph::get_next_from_frontier() {
		Node_Id node_id = nodes[frontier.front()].get_id();
		frontier.pop_front();
		return node_id;
	}

	bool Graph::is_frontier_empty() {
		return frontier.size() == 0;
	}

	Node_Id Graph::create_node(State state, Node_Id parent) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, parent, false);
		nodes[parent.id].add_child(node_id);
		return node_id;
	}

	Node_Id Graph::create_root_node(State state) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, Node_Id{ 0 }, true);
		return node_id;
	}

	void Graph::add_to_frontier(Node_Id node_id) {
		if (node_id.id < size_t{ 0 } || node_id.id >= size_t{ nodes.size() }) {
			throw;
		}
		frontier.push_back(node_id.id);
	}

	Node& Graph::get_node(Node_Id node_id) {
		return nodes[node_id.id];
	}
}