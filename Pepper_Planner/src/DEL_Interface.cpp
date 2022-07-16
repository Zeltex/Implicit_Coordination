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
	
	const Action* DEL_Interface::get_next_action()
	{
		return policy.is_solved() ? policy.get_action(domain.get_current_state(), domain.get_agents()) : nullptr;
	}

	bool DEL_Interface::query(const Formula& query) 
	{
		return domain.get_current_state().valuate(query, domain);
	}
	
	void DEL_Interface::perform_action(const Action* action)
	{	
		domain.perform_action(action);
	}

	void DEL_Interface::perform_action(const std::string& name, const std::vector<std::string>& arguments)
	{
		domain.perform_action(name, arguments);
	}

	bool DEL_Interface::create_policy(const std::string& planning_agent_name, const bool is_benchmark) 
	{
		const Agent* planning_agent = domain.get_agent(planning_agent_name);
		policy = planner.find_policy(domain, planning_agent, is_benchmark);
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() 
	{
		return domain.get_current_state().valuate(domain.get_goal(), domain);
	}

	std::string DEL_Interface::get_state_print() const
	{
		State contracted_state = domain.get_current_state().contract();
		contracted_state.shift_perspective(domain.get_agent(Agent_Id{ 0 }));
		return contracted_state.to_string(domain) + std::string("\nHash ") + std::to_string(contracted_state.to_hash());
	}

	const State& DEL_Interface::get_current_state() const
	{
		return domain.get_current_state();
	}

	std::string DEL_Interface::get_action_print(const Action* action) const
	{
		return action->to_string();
	}

	const Proposition_Instance* DEL_Interface::prop(const std::string& name, const std::string& arg_0)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0 });
	}

	const Proposition_Instance* DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1 });
	}

	const Proposition_Instance* DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2 });
	}

	const Proposition_Instance* DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2, arg_3 });
	}

	const Proposition_Instance* DEL_Interface::prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
	{
		return domain.get_propositions_lookup().get(Proposition_Instance{ domain.get_atom_lookup(), name, arg_0, arg_1, arg_2, arg_3, arg_4 });
	}

	const Agent* DEL_Interface::agent(const std::string& name)
	{
		return domain.get_agents()->get(name);
	}
}