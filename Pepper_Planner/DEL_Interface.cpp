#include "DEL_Interface.hpp"

namespace del {

	//DEL_Interface::DEL_Interface(State initial_state, Action_Library library) 
	//	: domain(initial_state), has_policy(false), policy(false), action_library(), pepper_id({ 0 }) {
	//	action_library = std::move(library);
	//}

	DEL_Interface::DEL_Interface(std::string file_path) :
		has_policy(false), 
		policy(false), 
		action_library(), 
		pepper_id({ 0 }),
		domain(Loader(file_path).get())
		{
		Loader loader(file_path);
		General_Domain general_domain = loader.get();


		// TODO - Adapt to new system
		//auto [domain, library, goal] = domain_interface.get_loaded();
		//this->domain = std::move(domain);
		//this->action_library = std::move(library);
		//this->goal = std::move(goal);
	}
	
	Interface_DTO DEL_Interface::get_next_action() {
		if (has_policy) {
			auto action_optional = policy.get_action(domain.get_current_state());
			if (action_optional.has_value()) {
				auto& action = action_optional.value();
				std::string announce_string = "";
				if (action.get_owner() == pepper_id) {
					const auto& events = action.get_events();
					if (events.size() > 0) {
						announce_string = events.get_first_event().get_preconditions().to_string(domain);
					}
				}
				return Interface_DTO(action, announce_string);
			}
		}
		return Interface_DTO();
		
	}

	bool DEL_Interface::query(const Formula& query) {
		return domain.get_current_state().valuate(query, domain);
	}
	
	void DEL_Interface::perform_action(Action action) {
		const State& current_state = domain.get_current_state();
		// TODO - Handle an inapplicable action here
		std::optional<State> product_update = current_state.product_update(action, domain);
		if (product_update.has_value())
		{
			product_update.value().contract();
			domain.add_new_current_state(product_update.value());
			PRINT_ACTION_TO_CONSOLE(action, *(this));
		}
		else
		{
			throw std::invalid_argument("Performed invalid action");
		};
	}

	void DEL_Interface::perform_action(const std::string& name, const std::string& owner, const std::vector<std::string>& arguments) {
		Atoms temp_arguments;
		temp_arguments.reserve(arguments.size());
		for (auto& argument : arguments) {
			temp_arguments.insert(domain.get_atom(argument));
		}

		auto action = Action(action_library.get_general_action(name), domain, temp_arguments);
		perform_action(action);

	}
	
	bool DEL_Interface::create_policy(Formula goal, const std::string& planning_agent, const bool is_benchmark) {
		this->goal = std::move(goal);
		return create_policy(planning_agent, is_benchmark);
	}

	bool DEL_Interface::create_policy(const std::string& planning_agent_name, const bool is_benchmark) {
		const Agent& planning_agent = domain.get_agent(planning_agent_name);
		policy = planner.find_policy(this->goal, action_library, domain, planning_agent, is_benchmark);
		has_policy = policy.is_solved();
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() {
		return domain.get_current_state().valuate(goal, domain);
	}
}