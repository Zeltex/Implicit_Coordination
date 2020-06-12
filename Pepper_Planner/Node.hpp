#pragma once

#include "State.hpp"
#include "Types.hpp"

namespace del {
	class Node {
	public:
		Node() = delete;
		Node(State state, Node_Id id) :state(state), id(id) {};
		State get_state();
		Node_Id get_id();

	private:
		State state;
		Node_Id id;
	};
}