#include "Interface_DTO.hpp"

namespace del {
	bool Interface_DTO::has_action() const {
		return has_an_action;
	}

	Action Interface_DTO::get_action() const {
		return action;
	}

	std::string Interface_DTO::get_announce_string() const {
		return announce_string;
	}
}