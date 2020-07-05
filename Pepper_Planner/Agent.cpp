#include "Agent.hpp"

namespace del {
	Agent_Id Agent::get_id() const {
		return id;
	}

	Atom_Id Agent::get_atom_id() const {
		return atom_id;
	}

	std::string Agent::get_name() const {
		return name;
	}
}