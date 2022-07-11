#pragma once
#include <optional>
#include <unordered_map>

#include "Types.hpp"

namespace del {
	class Action;
	class Graph;
	class State;
	class NodeOr;
	class NodeAnd;

	class Node_Comparator
	{
	public:
		Node_Comparator() {};
		Node_Comparator(NodeAnd* root_node);
		bool does_bisimilar_exist(const State& state, NodeOr* parent, const Action* action) const;
		bool does_bisimilar_exist(const State& state, NodeAnd* parent) const;
		void insert(NodeAnd* node);
		void insert(NodeOr* node);

	private:
		std::unordered_map<size_t, NodeAnd*> visited_and;
		std::unordered_map<size_t, NodeOr*> visited_or;
	};
}

