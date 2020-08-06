#include "Node_Comparator.hpp"
#include "State.hpp"
#include "DEL_Operations.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Core.hpp"

namespace del {

	Node_Comparator::Node_Comparator(const Node& node) {
		insert(node);
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_and(const Graph& graph, const State& state, Node_Id parent_id) const {
#if ON_PATH_ENABLED == 1
	#if BISIMILAR_USE_HASH_ENABLED == 1
		if (is_bisimilar_on_path(graph, parent_id, state)) return { true, {} };
	#else 
		//return does_bisimilar_exist_brute(graph, state, Node_Type::Or);
	#endif
#endif


#if BISIM_COMPARISON_ENABLED == 1
	#if BISIMILAR_USE_HASH_ENABLED == 1
		return does_bisimilar_exist(graph, state, visited_and);
	#else 
		return does_bisimilar_exist_brute(graph, state, Node_Type::And);
	#endif
#else
		return { false, {} };
#endif
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_or(const Graph& graph, const State& state, Node_Id parent_id) const{
#if ON_PATH_ENABLED == 1
	#if BISIMILAR_USE_HASH_ENABLED == 1
		if (is_bisimilar_on_path(graph, parent_id, state)) return { true, {} };
	#else 
		//return does_bisimilar_exist_brute(graph, state, Node_Type::Or);
	#endif
#endif
#if BISIM_COMPARISON_ENABLED == 1
	#if BISIMILAR_USE_HASH_ENABLED == 1
		return does_bisimilar_exist(graph, state, visited_or);
	#else 
		return does_bisimilar_exist_brute(graph, state, Node_Type::Or);
	#endif
#else
		return { false, {} };
#endif
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist(const Graph& graph, const State& state, const std::unordered_map<size_t, Node_Id>& visited) const {
		auto hash = state.to_hash();
		while (true) {
			auto potential_match = visited.find(hash);
			if (potential_match == visited.end()) {
				return { false, {} };
			}
			if (are_states_bisimilar(graph.get_const_node((*potential_match).second).get_state(), state)) {
				return { true, (*potential_match).second };
			}
			++hash;
		}
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_brute(const Graph& graph, const State& state, Node_Type type) const {
		for (const auto& node : graph.get_const_nodes()) {
			if (node.get_type() != type) continue;
			if (are_states_bisimilar(node.get_state(), state)) {
				return { true, {node.get_id()} };
			}
		}
		return { false, {} };
	}

	void Node_Comparator::insert(const Node& node) {
		if (node.get_type() == Node_Type::And) {
			insert(node, visited_and);
		} else {
			insert(node, visited_or);
		}

	}
	void Node_Comparator::insert(const Node& node, std::unordered_map<size_t, Node_Id>& visited) {
		auto hash = node.get_hash();
		while (true) {
			if (visited.find(hash) == visited.end()) {
				visited.insert({ hash, node.get_id() });
				return;
			}
			++hash;
		}

	}

	bool Node_Comparator::is_bisimilar_on_path(const Graph& graph, Node_Id parent_id, const State& state) const {

		std::deque<Node_Id> frontier;
		for (auto& parent_of_parent : graph.get_const_node(parent_id).get_parents()) frontier.push_back(parent_of_parent.first);
		std::unordered_set<size_t> visited;
		auto hash = state.to_hash();

		while (!frontier.empty()) {
			Node_Id current_node_id = frontier.front();
			frontier.pop_front();
			auto& current_node = graph.get_const_node(current_node_id);

			if (current_node.get_hash() == hash && are_states_bisimilar(current_node.get_state(), state)) {
				return true;
			}

			for (auto& parent1_entry : current_node.get_parents()) {
				for (auto& parent2_entry : graph.get_const_node(parent1_entry.first).get_parents()) {
					auto parent2_id = parent2_entry.first;
					if (visited.find(parent2_id.id) != visited.end()) {
						continue;
					}

					visited.insert(parent2_id.id);
					frontier.push_back(parent2_id);
				}
			}
		}
		return false;
	}

	bool Node_Comparator::is_bisimilar_on_path_brute(const Graph& graph, Node_Id parent_id, const State& state) const {

		std::deque<Node_Id> frontier;
		for (auto& parent_of_parent : graph.get_const_node(parent_id).get_parents()) frontier.push_back(parent_of_parent.first);
		std::unordered_set<size_t> visited;

		while (!frontier.empty()) {
			Node_Id current_node_id = frontier.front();
			frontier.pop_front();
			auto& current_node = graph.get_const_node(current_node_id);

			if (are_states_bisimilar(current_node.get_state(), state)) {
				return true;
			}

			for (auto& parent1_entry : current_node.get_parents()) {
				for (auto& parent2_entry : graph.get_const_node(parent1_entry.first).get_parents()) {
					auto parent2_id = parent2_entry.first;
					if (visited.find(parent2_id.id) != visited.end()) {
						continue;
					}

					visited.insert(parent2_id.id);
					frontier.push_back(parent2_id);
				}
			}
		}
		return false;
	}
}