#include "DEL_Interface.hpp"

#include "Core.hpp"
#include "Loader.hpp"

#include <fstream>

namespace del 
{
	DEL_Interface::DEL_Interface(const std::string& file_path) :
		policy(false),
		domain(Loader(file_path).get())
	{

	}
	
	std::optional<Action> DEL_Interface::get_next_action() 
	{
		return policy.is_solved() ? policy.get_action(domain.get_current_state()) : std::optional<Action>{};
	}

	bool DEL_Interface::query(const Formula& query) 
	{
		return domain.get_current_state().valuate(query, domain);
	}
	
	void DEL_Interface::perform_action(Action action) 
	{	
		domain.perform_action(action);
	}

	void DEL_Interface::perform_action(const std::string& name, const std::vector<std::string>& arguments)
	{
		domain.perform_action(name, arguments);
	}
	
	bool DEL_Interface::create_policy(Formula goal, const std::string& planning_agent, const bool is_benchmark) 
	{	
		this->goal = std::move(goal);
		return create_policy(planning_agent, is_benchmark);
	}

	bool DEL_Interface::create_policy(const std::string& planning_agent_name, const bool is_benchmark) 
	{
		const Agent& planning_agent = domain.get_agent(planning_agent_name);
		policy = planner.find_policy(this->goal, domain.get_action_library(), domain, planning_agent, is_benchmark);
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() 
	{
		return domain.get_current_state().valuate(goal, domain);
	}

	std::string DEL_Interface::get_state_print() const
	{
		return domain.get_current_state().to_string(domain);
	}

	Proposition DEL_Interface::prop(const std::string& name, const std::string& arg_0)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0 });
	}

	Proposition DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1 });
	}

	Proposition DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2 });
	}

	Proposition DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2, arg_3 });
	}

	Proposition DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2, arg_3, arg_4 });
	}

	Agent_Id DEL_Interface::agent(const std::string& name)
	{
		return domain.get_agents().get(name).get_id();
	}
}