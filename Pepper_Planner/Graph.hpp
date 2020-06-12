#pragma once

#include <queue>

#include "Node.hpp"

namespace del {
	class Graph {
	public:
		Node& get_next_from_frontier();
		bool is_frontier_empty();
		void add_to_frontier(Node node);
	private:
		std::queue<int> frontier;
		std::vector<Node> nodes;
	};
}