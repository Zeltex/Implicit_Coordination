#include "Agent.hpp"

namespace del {
	Agent_Id Agent::get_id() const {
		return id;
	}

	std::string Agent::get_name() const {
		return name;
	}
}