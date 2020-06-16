#pragma once

#include <string>

#include "Types.hpp"

namespace del {
	class Agent {
	public:
		Agent(Agent_Id id, std::string name) : id(id), name(name){}
		Agent_Id get_id() const;
		std::string get_name() const;
	private:
		Agent_Id id;
		std::string name;
	};
}