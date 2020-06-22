#include "Node.hpp"
#include "Graph.hpp"

namespace del {
	const State& Node::get_state() const {
		return state;;
	}

	Action Node::get_action() {
		return action_from_parent;
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

	const std::vector<Node_Id>& Node::get_children() const {
		return children;
	}

	Node_Type Node::get_type() const {
		return type;
	}

	const Action& Node::get_parent_action() const {
		return action_from_parent;
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
		std::string type_string = type_to_string();


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

		result += ")\n--- Action from parent\n" +  (type == Node_Type::Or ? "Agent split, no action" : action_from_parent.to_string()) + " \n" + state.to_string();
		return result;
	}

	std::string Node::to_graph(const std::vector<Agent> agents, const std::string node_id, const std::string state_id) const {
		std::string result = "subgraph cluster_" + node_id + " {\nlabel=\"(" + type_to_string() + ")Node " + node_id + "\";\n";
		if (solved) {
			result += "pencolor=green;\n";
		} else if (dead) {
			result += "pencolor=red;\n";
		}
		result += state.to_graph(agents, state_id) + "\n}";
		return result;
	}

	std::string Node::type_to_string() const {
		switch (type) {
		case Node_Type::And: return "And"; break;
		case Node_Type::Or: return "Or"; break;
		default: return "Unknown";
		}
	}
}