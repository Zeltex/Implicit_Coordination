#pragma once

#include <vector>
#include <string>

#include "Domain.hpp"
#include "Action.hpp"
#include "Planner.hpp"
#include "Interface_DTO.hpp"
#include "Action_Library.hpp"
#include "Environment_Loader.hpp"

namespace del {
	class DEL_Interface {
	public:
		DEL_Interface();
		DEL_Interface(State initial_state);
		Interface_DTO get_next_action();
		void perform_do(const Agent_Id i, const std::vector<std::string>& add, const std::vector<std::string>& del);
		void perform_action(Action action);
		bool create_policy(Formula goal);
		bool create_policy();
	private:
		Domain domain;
		Planner planner;
		bool has_policy;
		Policy policy;
		Action_Library action_library;
		Agent_Id pepper_id;
		Formula default_goal;
	};
}