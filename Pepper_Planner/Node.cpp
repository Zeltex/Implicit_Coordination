#include "Node.hpp"
#include "Graph.hpp"

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

	bool Node::is_root_node() const {
		return root;
	}

	bool Node::valuate(const Formula& formula) const {
		return state.valuate(formula);
	}

	bool Node::is_dead() const {
		return dead;
	}

	bool Node::is_solved() const {
		return solved;
	}

	void Node::set_dead() {
		dead = true;
	}

	void Node::set_solved() {
		solved = true;
	}

	bool Node::check_if_dead(Graph& graph) {
		if (dead) {
			return true;
		}
		else if (solved) {
			return false;
		}

		if (type == Node_Type::And) {
			return check_if_dead_and(graph);
		}
		else if (type == Node_Type::Or) {
			return check_if_dead_or(graph);
		}
		else {
			dead = true;
			return true;
		}
	}
	bool Node::check_if_dead_and(Graph& graph) {
		for (auto child : children) {
			if (graph.get_node(child).is_dead()) {
				dead = true;
				return true;
			}
		}
		return false;
	}
	bool Node::check_if_dead_or(Graph& graph) {
		for (auto child : children) {
			if (!graph.get_node(child).is_dead()) {
				return false;
			}
		}
		dead = true;
		return true;
	}

	bool Node::check_if_solved(Graph& graph) {
		if (solved) {
			return true;
		}
		else if (dead) {
			return false;
		}

		if (type == Node_Type::And) {
			return check_if_solved_and(graph);
		}
		else if (type == Node_Type::Or) {
			return check_if_solved_or(graph);
		}
		else {
			solved = false;
			return false;
		}
	}
	bool Node::check_if_solved_or(Graph& graph) {
		for (auto child : children) {
			if (graph.get_node(child).is_solved()) {
				solved = true;
				return true;
			}
		}
		return false;
	}
	bool Node::check_if_solved_and(Graph& graph) {
		for (auto child : children) {
			if (!graph.get_node(child).is_solved()) {
				return false;
			}
		}
		solved = true;
		return true;
	}

	std::string Node::to_string() const {
		std::string type_string;
		switch(type) {
		case Node_Type::And: type_string = "And"; break;
		case Node_Type::Or: type_string = "Or"; break;
		default: type_string = "Unknown";
		}

		std::string result = "---- Node " + std::to_string(id.id)
			+ ": (Type, " + type_string
			+ ") (Parent, " + std::to_string(parent.id)
			+ ") (Root, " + (root ? "True" : "False")
			+ ") (Dead, " + (dead ? "True" : "False")
			+ ") (Solved, " + (solved ? "True" : "False")
			+ ") (Children, ";
		bool first = true;
		for (auto child : children) {
			if (first) {
				first = false;
			} else {
				result += ", ";
			}
			result += std::to_string(child.id);
		}

		result += ")\n--- Action from parent\n" +  (type == Node_Type::And ? "Agent split, no action" : action_from_parent.to_string()) + " \n" + state.to_string();
		return result;
	}
}