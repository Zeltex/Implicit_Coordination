#pragma once

#include <tuple>

#include "Domain.hpp"
#include "Action_Library.hpp"

namespace del {
	class Environment_Loader {
	public:
		std::tuple<Domain, Action_Library, Formula> load(size_t environment_number);
	private:
		std::tuple<Domain, Action_Library, Formula> load_0();

		Formula get_goal_formula();
		void add_announce_action(Action_Library& library, std::string proposition, size_t amount_of_agents);
		void add_pickup_action(Action_Library& library, std::string from, std::string to, size_t amount_of_agents);
		void add_perceive_action(Action_Library& library, std::string proposition, size_t amount_of_agents);
		void add_actions(Action_Library& library, size_t amount_of_agents);
		State get_initial_state(size_t amount_of_agents);
	};
}