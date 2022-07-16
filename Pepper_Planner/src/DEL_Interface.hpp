#pragma once

#include <vector>
#include <string>

#include "Action.hpp"
#include "Domain.hpp"
#include "Planner.hpp"
#include "Types.hpp"

namespace del {
	class DEL_Interface {
	public:
		DEL_Interface(const std::string& file_path);

		const Action* get_next_action();
		std::string get_action_print(const Action* action) const;
		std::string get_state_print() const;
		const State& get_current_state() const;
		void perform_action(const Action* action);
		void perform_action(const std::string& name, const std::vector<std::string>& arguments);
		bool create_policy(Formula goal, const std::string& planning_agent, const bool is_benchmark=false);
		bool create_policy(const std::string& planning_agent, const bool is_benchmark=false);
		bool is_solved();
		bool query(const Formula& query);

		const Proposition_Instance* prop(const std::string& name, const std::string& arg_0);
		const Proposition_Instance* prop(const std::string& name, const std::string& arg_0, const std::string& arg_1);
		const Proposition_Instance* prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2);
		const Proposition_Instance* prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);
		const Proposition_Instance* prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4);
		const Agent* agent(const std::string& name);

	private:
		Domain domain;
		Planner planner;
		Policy policy;
	};
}
