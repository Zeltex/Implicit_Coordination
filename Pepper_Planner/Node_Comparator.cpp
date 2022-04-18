#include "Node_Comparator.hpp"
#include "State.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Core.hpp"

namespace del {

	Node_Comparator::Node_Comparator(const Node& node) {
		insert(node);
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_and(const Graph& graph, const State& state) const {
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

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_or(const Graph& graph, const State& state) const{
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
			const State& temp_state = graph.get_const_node((*potential_match).second).get_state();
			if (temp_state.is_bisimilar_to(state)) {
				return { true, (*potential_match).second };
			}
			++hash;
		}
	}

	std::pair<bool, std::optional<Node_Id>> Node_Comparator::does_bisimilar_exist_brute(const Graph& graph, const State& state, Node_Type type) const {
		for (const auto& node : graph.get_const_nodes()) {
			if (node.get_type() != type) continue;
			if (node.get_state().is_bisimilar_to(state)) {
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
}