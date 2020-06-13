#include "Node.hpp"

namespace del {
	State& Node::get_state() {
		return state;;
	}

	Node_Id Node::get_id() {
		return id;
	}

	void Node::add_child(Node_Id node) {
		children.push_back(node);
	}

	Node_Id Node::get_parent() {
		return parent;
	}

	std::vector<Node_Id>& Node::get_children() {
		return children;
	}

	bool Node::is_root_node() {
		return is_root;
	}

	bool Node::valuate(Formula& formula) {
		return state.valuate(formula);
	}
}