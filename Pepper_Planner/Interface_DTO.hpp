#pragma once

#include <string>

#include "Action.hpp"

namespace del {
	class Interface_DTO {
	public:
		Interface_DTO() : has_an_action(false), action(), announce_string() {}
		Interface_DTO(Action action, std::string announce_string) : has_an_action(true), action(action), announce_string(announce_string) {}
		bool has_action() const;
		Action get_action() const;
		std::string get_announce_string() const;
	private:
		bool has_an_action;
		Action action;
		std::string announce_string;
	};
}