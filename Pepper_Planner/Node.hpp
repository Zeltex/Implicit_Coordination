#pragma once

#include <vector>

#include "State.hpp"
#include "Types.hpp"

namespace del {
	class Node {
	public:
		Node() = delete;
		Node(State state, Node_Id id, Node_Id parent, bool is_root) :
			state(state), id(id), parent(parent), is_root(is_root) {};
		void add_child(Node_Id node);
		State& get_state();
		Node_Id get_id();
		Node_Id get_parent();
		std::vector<Node_Id>& get_children();
		bool is_root_node();

	private:
		State state;
		Node_Id id;
		Node_Id parent;
		bool is_root;
		std::vector<Node_Id> children;
	};
}