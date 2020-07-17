#include "Graph.hpp"

namespace del {
	Node_Id Graph::get_next_from_frontier() {
		Node_Id node_id = frontier.top().id;
		frontier.pop();
		return node_id;
	}

	bool Graph::is_frontier_empty() {
		return frontier.size() == 0;
	}

	Node_Id Graph::create_or_node(State state, Node_Id parent) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, parent, false);
		nodes[parent.id].add_child(node_id);
		return node_id;
	}

	Node_Id Graph::create_and_node(State state, Node_Id parent, Action action_from_parent) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, parent, action_from_parent, false);
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
		frontier.emplace(node_id, nodes.at(node_id.id).get_cost());
	}

	Node& Graph::get_node(Node_Id node_id) {
		return nodes[node_id.id];
	}

	Node& Graph::get_root_node() {
		return nodes[root.id];
	}

	std::string Graph::to_string(const Domain& domain) const {
		std::string result = "Graph: (root, " + std::to_string(root.id) + ") (frontier";
		//for (auto node_id : frontier) {
		//	result += ", " + std::to_string(node_id);
		//}
		result += ")";
		for (auto node : nodes) {
			result += "\n\n\n" + node.to_string(domain);
		}
		return result;
	}

	std::string Graph::to_graph(const Domain& domain) const {
		std::string result = "digraph G {\ncompound=true;";
		std::string connections;

		size_t counter = 0;
		for (auto& node : nodes) {
			result += "\n" + node.to_graph(std::to_string(counter), "s" + std::to_string(counter), domain);
			
			for (auto& child : node.get_children()) {
				std::string left = "s" + std::to_string(counter) + "0";
				std::string right = "s" + std::to_string(child.id) + "0";

				connections += "\n" + left + " -> " + right + "[ltail=cluster_" + std::to_string(counter) + ", lhead=cluster_" + std::to_string(child.id);

				if (nodes[child.id].get_type() == Node_Type::And) {
					connections += ",label=\"" + nodes[child.id].get_parent_action(node.get_id()).to_compact_string(domain) + "\"";
				}
					
				connections += "];";
			}
			counter++;
		}
		result += connections + "\n}";


		return result;
	}

	std::string Graph::to_partial_graph(const Domain& domain) const {
		std::string result = "digraph G {\ncompound=true;";
		std::string connections;

		size_t counter = 0;
		std::deque<size_t> frontier = { root.id };

		while (!frontier.empty()) {
			auto node_id = frontier.front();
			auto& node = nodes.at(node_id);
			counter = node_id;
			frontier.pop_front();
			result += "\n" + node.to_graph(std::to_string(counter), "s" + std::to_string(counter), domain);

			if (node.is_solved()) {
				for (auto& child : node.get_children()) {

					frontier.push_back(child.id);

					std::string left = "s" + std::to_string(counter) + "0";
					std::string right = "s" + std::to_string(child.id) + "0";

					connections += "\n" + left + " -> " + right + "[ltail=cluster_" + std::to_string(counter) + ", lhead=cluster_" + std::to_string(child.id);

					if (nodes[child.id].get_type() == Node_Type::And) {
						connections += ",label=\"" + nodes[child.id].get_parent_action(node.get_id()).to_compact_string(domain) + "\"";
					}

					connections += "];";
				}
			}
			counter++;
		}
		result += connections + "\n}";


		return result;
	}
}