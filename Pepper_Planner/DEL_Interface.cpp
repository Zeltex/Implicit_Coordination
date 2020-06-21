#include "DEL_Interface.hpp"

namespace del {

	DEL_Interface::DEL_Interface(size_t domain_to_load) : domain(1), planner(), has_policy(false), policy(false), action_library(1), pepper_id({ 0 }) {
		Environment_Loader environment_loader;
		auto [domain, action_library, goal] = environment_loader.load(domain_to_load);
		this->domain = domain;
		this->action_library = std::move(action_library);
		this->goal = std::move(goal);
	}
	
	DEL_Interface::DEL_Interface(State initial_state, Action_Library library) : domain(initial_state.get_number_of_agents(), initial_state), has_policy(false), policy(false), action_library(2), pepper_id({ 0 }) {
		domain = Domain(initial_state.get_number_of_agents(), initial_state);
		action_library = std::move(library);
	}
	
	Interface_DTO DEL_Interface::get_next_action() {
		if (has_policy) {
			auto [action, solved] = policy.get_action(domain.get_current_state());
			if (solved) {
				std::string announce_string = "";
				if (action.get_owner() == pepper_id) {
					auto& events = action.get_events();
					if (events.size() > 0) {
						announce_string = events[0].get_preconditions().to_string();
					}
				}
				return Interface_DTO(action, announce_string);
			}
		} else {
			return Interface_DTO();
		}
	}
	
	void DEL_Interface::perform_do(const Agent_Id i, const std::vector<Proposition_Instance>& add, const std::vector<Proposition_Instance>& del) {
		domain.perform_do(i, add, del);
	}
	
	void DEL_Interface::perform_action(Action action) {
		domain.perform_action(action);
	}
	
	bool DEL_Interface::create_policy(Formula goal) {
		this->goal = std::move(goal);
		policy = planner.find_policy(this->goal, action_library, domain.get_current_state());
		has_policy = policy.is_solved();
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() {
		return domain.get_current_state().valuate(goal);
	}
}