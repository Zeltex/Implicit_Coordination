#include "Graph.hpp"

namespace del {
	Node& Graph::get_next_from_frontier() {
		throw;
	}

	bool Graph::is_frontier_empty() {
		throw;
	}

	Node& Graph::create_node(State state) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id);
		return nodes.at(node_id.id);
	}

	void Graph::add_to_frontier(Node_Id node_id) {
		if (node_id.id < 0 || node_id.id >= nodes.size()) {
			throw;
		}
		frontier.push(node_id.id);
	}

	void Graph::add_parent_child_relation(Node_Id parent, Node_Id child) {
		throw;
	}

}