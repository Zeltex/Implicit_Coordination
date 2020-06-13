#pragma once

#include <vector>

#include "Action.hpp"

namespace del {
	class Action_Library {
	public:

		std::vector<Action>& get_actions();
	private:

		std::vector<Action> actions;

	};
}