#include "Graph.hpp"
#include "Node_Comparator.hpp"
#include "Core.hpp"

namespace del {


	Graph::Graph(size_t node_size, const State& state, Node_Comparator& history, Agent_Id planning_agent) {
		nodes.reserve(node_size); 
		auto root = create_root_node(state);
		history.insert(nodes.at(root.id));
//		auto local = std::move(perform_perspective_shift(state, planning_agent));
//#if BISIM_CONTRACTION_ENABLED == 1
//		local = std::move(perform_k_bisimilar_contraction(local, BISIMILAR_DEPTH));
//#endif
//		local.remove_unreachable_worlds();
//		for (auto& global : split_into_global_states(local, planning_agent)) {
//
//			auto node = create_or_node(std::move(global), root);
//			history.insert(nodes.at(node.id));
//			add_to_frontier(node);
//		}

		for (auto& global : split_into_global_states(state, planning_agent)) {

			auto node = create_or_node(std::move(global), root);
			history.insert(nodes.at(node.id));
			add_to_frontier(node);
		}
	}

	Node_Id Graph::get_next_from_frontier() {
		Node_Id node_id = frontier.top().id;
		frontier.pop();
		return node_id;
	}

	bool Graph::is_frontier_empty() const {
		return frontier.size() == 0;
	}

	Node& Graph::create_or_node(State state, const Node& parent) {
		return create_or_node(state, parent.get_id());
	}

	Node& Graph::create_or_node(State state, Node_Id parent) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, parent, false);
		Node& node = nodes.back();
		node.calculate_hash();
		nodes[parent.id].add_child(node_id);
		return node;
	}

	Node& Graph::create_and_node(State state, Node_Id parent, Action action_from_parent) {
		Node_Id node_id = Node_Id{ nodes.size() };
		nodes.emplace_back(state, node_id, parent, action_from_parent, false);
		Node& node = nodes.back();
		node.calculate_hash();
		nodes[parent.id].add_child(node_id);
		return node;
	}

	Node& Graph::create_root_node(State state) {
		Node_Id node_id = Node_Id{ nodes.size() };
		// The dummy action makes sure root is and-node
		nodes.emplace_back(state, node_id, Node_Id{ 0 }, Action{ }, true);
		Node& node = nodes.back();
		node.calculate_hash();
		root = node_id;
		return node;
	}

	void Graph::add_to_frontier(const Node& node) {
		add_to_frontier(node.get_id());
	}

	void Graph::add_to_frontier(Node_Id node_id) {
		if (node_id.id < size_t{ 0 } || node_id.id >= size_t{ nodes.size() }) {
			throw;
		}
		frontier.emplace(node_id, nodes.at(node_id.id).get_cost());
	}

	void Graph::set_parent_child(const Node& parent, Node_Id child_id, const Action& action) {
		set_parent_child(parent.get_id(), child_id, action);
	}

	void Graph::set_parent_child(Node_Id parent_id, Node_Id child_id, const Action& action) {
		get_node(child_id).add_parent(parent_id, action);
		get_node(parent_id).add_child(child_id);
	}

	void Graph::set_parent_child(Node_Id parent_id, Node_Id child_id) {
		get_node(child_id).add_parent(parent_id);
		get_node(parent_id).add_child(child_id);
	}

	const std::vector<Node>& Graph::get_const_nodes() const {
		return nodes;
	}

	std::vector<Node>& Graph::get_nodes() {
		return nodes;
	}

	const Node& Graph::get_const_node(Node_Id node_id) const {
		return nodes.at(node_id.id);
	}

	Node& Graph::get_node(Node_Id node_id) {
		return nodes.at(node_id.id);
	}

	const Node& Graph::get_node(Node_Id node_id) const
	{
		return nodes.at(node_id.id);
	}

	Node& Graph::get_root_node() {
		return nodes.at(root.id);
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

}
