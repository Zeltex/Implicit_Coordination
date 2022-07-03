#pragma once
#include <optional>
#include <unordered_map>

#include "Types.hpp"

namespace del {
	class Graph;
	class State;
	class Node;

	class Node_Comparator
	{
	public:
		Node_Comparator() {};
		Node_Comparator(Node* node);
		Node* does_bisimilar_exist_and(const Graph& graph, const State& state) const;
		Node* does_bisimilar_exist_or(const Graph& graph, const State& state) const;
		void insert(Node* node);

	private:
		Node* does_bisimilar_exist(const Graph& graph, const State& state, const std::unordered_map<size_t, Node*>& visited) const;
		Node* does_bisimilar_exist_brute(const Graph& graph, const State& state, Node_Type type) const;
		void insert(Node* node, std::unordered_map<size_t, Node*>& visited);

		std::unordered_map<size_t, Node*> visited_and;
		std::unordered_map<size_t, Node*> visited_or;
	};
}

