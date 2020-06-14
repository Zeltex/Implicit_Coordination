#pragma once

#include "Types.hpp"

namespace del {
	class Agent {
	public:
		Agent(Agent_Id id) : id(id) {}
		Agent_Id get_id() const;
	private:
		Agent_Id id;
	};
}