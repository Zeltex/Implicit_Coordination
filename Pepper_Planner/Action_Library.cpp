#include "Action_Library.hpp"

namespace del {

	Action_Library::Action_Library(size_t amount_of_agents) {
		agents.reserve(amount_of_agents);
		for (size_t i = 0; i < amount_of_agents; i++) {
			agents.emplace_back(Agent_Id{ i });
		}
	}

	const std::vector<Action>& Action_Library::get_actions() const{
		return actions;
	}

	const std::vector<Agent>& Action_Library::get_agents() const {
		return agents;
	}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}
}