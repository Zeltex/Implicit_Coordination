#include "Node.hpp"

namespace del {
	State Node::get_state() {
		throw;
	}

	Node_Id Node::get_id() {
		return id;
	}
}