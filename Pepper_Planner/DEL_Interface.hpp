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
		DEL_Interface(size_t domain_to_load);
		DEL_Interface(State initial_state, Action_Library library);
		Interface_DTO get_next_action();
		void perform_do(const Agent_Id i, const std::vector<std::string>& add, const std::vector<std::string>& del);
		void perform_action(Action action);
		bool create_policy(Formula goal);
		bool is_solved();
	private:
		Domain domain;
		Planner planner;
		bool has_policy;
		Policy policy;
		Action_Library action_library;
		Agent_Id pepper_id;
		Formula goal;
	};
}