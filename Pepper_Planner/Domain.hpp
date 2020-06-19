#pragma once

#include <vector>
#include <string>

#include "Types.hpp"
#include "State.hpp"
#include "../Formula/Formula.hpp"
#include "Action_Event.hpp"
#include "Action.hpp"
#include "DEL_Operations.hpp"

namespace del {
	class Domain {
	public:

		Domain(size_t amount_of_agents) : amount_of_agents(amount_of_agents), states() {}
		Domain(size_t amount_of_agents, State initial_state) : amount_of_agents(amount_of_agents), states({ initial_state }) {}

		void perform_do(const Agent_Id i, const std::vector<std::string>& add, const std::vector<std::string>& del);
		void perform_action(Action action);
		State get_current_state() const;
	private:
		size_t amount_of_agents;
		std::vector<State> states;
	};
}