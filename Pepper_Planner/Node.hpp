#pragma once

#include "State.hpp"

namespace del {
	class Node {
	public:
		Node(State state) :state(state) {};
		void add_child(Node node);
		State get_state();

	private:
		State state;
	};
}