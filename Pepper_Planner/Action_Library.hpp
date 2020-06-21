#pragma once

#include <vector>
#include <iostream>

#include "General_Action.hpp"
#include "Action.hpp"
#include "Agent.hpp"
#include "Domain.hpp"

namespace del {
	class Action_Library {
	public:
		Action_Library();
		Action_Library(size_t amount_of_agents);
		void set_amount_of_agents(size_t amount_of_agents);
		const std::vector<Action>& get_actions() const;
		void add_action(const Action& action);
		void set_announce_enabled();
		void add_general_action(const General_Action& action, const Domain& domain);
	private:
		bool announce_enabled;
		size_t amount_of_agents;
		std::vector<Action> actions;
	};
}