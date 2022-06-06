#include "DEL_Interface.hpp"

#include "Core.hpp"

#include <fstream>

namespace del {

	DEL_Interface::DEL_Interface(std::string file_path) :
		has_policy(false), 
		policy(false), 
		pepper_id({ 0 }),
		domain(Loader(file_path).get())
	{

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
		domain.perform_action(action);
	}

	void DEL_Interface::perform_action(const std::string& name, const std::vector<std::string>& arguments)
	{
		domain.perform_action(name, arguments);
	}
	
	bool DEL_Interface::create_policy(Formula goal, const std::string& planning_agent, const bool is_benchmark) {
		this->goal = std::move(goal);
		return create_policy(planning_agent, is_benchmark);
	}

	bool DEL_Interface::create_policy(const std::string& planning_agent_name, const bool is_benchmark) {
		const Agent& planning_agent = domain.get_agent(planning_agent_name);
		policy = planner.find_policy(this->goal, domain.get_action_library(), domain, planning_agent, is_benchmark);
		has_policy = policy.is_solved();
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() {
		return domain.get_current_state().valuate(goal, domain);
	}


	const Atom_Lookup& DEL_Interface::get_atom_lookup() const
	{
		return domain.get_atom_lookup();
	}

	const Propositions_Lookup& DEL_Interface::get_propositions_lookup() const
	{
		return domain.get_propositions_lookup();
	}

	const Agents& DEL_Interface::get_agent_lookup() const
	{
		return domain.get_agents();
	}

	std::string DEL_Interface::get_state_print() const
	{
		return domain.get_current_state().to_string(domain);
	}
}