#pragma once

#include <vector>

#include "Action.hpp"
#include "Agent.hpp"

namespace del {
	class Action_Library {
	public:
		Action_Library(size_t amount_of_agents);
		const std::vector<Action>& get_actions() const;
		const std::vector<Agent>& get_agents() const;
		void add_action(const Action& action);
	private:

		std::vector<Action> actions;
		std::vector<Agent> agents;
	};
}