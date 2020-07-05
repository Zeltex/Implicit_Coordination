#pragma once

#include <vector>
#include <iostream>

#include "General_Action.hpp"
#include "Action.hpp"
#include "Agent.hpp"
#include "Domain.hpp"
#include "Core.hpp"

namespace del {
	class Action_Library {
	public:
		Action_Library();
		Action_Library(size_t amount_of_agents);
		void set_amount_of_agents(size_t amount_of_agents);
		const std::vector<Action>& get_actions() const;
		const General_Action& get_general_action(std::string name) const;
		const std::vector<Action> get_announce_actions(State state, const Domain& domain) const;
		Action create_announce_action(Agent_Id owner, Proposition_Instance proposition, size_t amount_of_agents, const Domain& domain) const;
		void add_action(const Action& action);
		void set_announce_enabled();
		void add_general_action(const General_Action& action, const Domain& domain);
	private:
		bool increment_counters_success(std::vector<size_t>& counters, std::vector<std::vector<Atom_Id>>& atoms);

		bool announce_enabled;
		size_t amount_of_agents;
		std::vector<Action> actions;
		std::vector<General_Action> general_actions;
		std::unordered_map<std::string, size_t> general_action_name_to_id;
	};
}