#include "Node_Comparator.hpp"
#include "State.hpp"
#include "Graph.hpp"
#include "Node.hpp"
#include "Core.hpp"

namespace del {

	Node_Comparator::Node_Comparator(Node* node) 
	{
		insert(node);
	}

	Node* Node_Comparator::does_bisimilar_exist_and(const Graph& graph, const State& state) const
	{
		return does_bisimilar_exist(graph, state, visited_and);
	}

	Node* Node_Comparator::does_bisimilar_exist_or(const Graph& graph, const State& state) const
	{
		return does_bisimilar_exist(graph, state, visited_or);
	}

	Node* Node_Comparator::does_bisimilar_exist(const Graph& graph, const State& state, const std::unordered_map<size_t, Node*>& visited) const {
		auto hash = state.to_hash();
		auto match = visited.find(hash);
		return match == visited.end() ? nullptr : match->second;
	}

	Node* Node_Comparator::does_bisimilar_exist_brute(const Graph& graph, const State& state, Node_Type type) const {
		for (Node* node : graph.get_const_nodes()) 
		{
			if (node->get_type() != type)
			{
				continue;
			}

			if (node->get_state().is_bisimilar_to(state)) 
			{
				return node;
			}
		}
		return nullptr;
	}

	void Node_Comparator::insert(Node* node) 
	{
		if (node->get_type() == Node_Type::And) 
		{
			insert(node, visited_and);
		} 
		else 
		{
			insert(node, visited_or);
		}

	}
	void Node_Comparator::insert(Node* node, std::unordered_map<size_t, Node*>& visited) {
		auto hash = node->get_hash();
		while (true) 
		{
			if (visited.find(hash) == visited.end()) 
			{
				visited.insert({ hash, node });
				return;
			}
			++hash;
		}

	}
}