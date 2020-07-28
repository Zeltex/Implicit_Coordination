#pragma once
#include <optional>

#include "Types.hpp"

namespace del {
	class Graph;
	class State;
	class Node;
	class Node_Comparator
	{
	public:
		Node_Comparator() {};
		Node_Comparator(const Node& node);
		std::pair<bool, std::optional<Node_Id>> does_bisimilar_exist_and(const Graph& graph, const State& state, Node_Id parent_id) const;
		std::pair<bool, std::optional<Node_Id>> does_bisimilar_exist_or(const Graph& graph, const State& state, Node_Id parent_id) const;
		void insert(const Node& node);

	private:
		std::pair<bool, std::optional<Node_Id>> does_bisimilar_exist(const Graph& graph, const State& state, const std::unordered_map<size_t, Node_Id>& visited) const;
		void insert(const Node& node, std::unordered_map<size_t, Node_Id>& visited);
		bool is_bisimilar_on_path(const Graph& graph, Node_Id parent_id, const State& state) const;

		std::unordered_map<size_t, Node_Id> visited_and;
		std::unordered_map<size_t, Node_Id> visited_or;
	};
}

