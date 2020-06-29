#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>

#include "Action_Event.hpp"
#include "Types.hpp"
#include "Agent.hpp"

namespace del {
	class Action;
	class Domain;
	class General_Action {
	public:
		General_Action() {}
		void set_owner(std::string type, std::string name);
		void set_name(std::string name);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_action_input(std::vector<std::pair<std::string, std::string>> inputs);
		void create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list);
		void set_amount_of_agents(size_t amount_of_agents);
		void add_edge_condition(std::string agent, std::vector<Edge_Condition>&& edge_conditions);

		const std::vector<std::pair<std::string, std::string>>&				get_inputs() const;
		const std::vector<std::string>&										get_designated_events() const;
		const std::unordered_map<std::string, std::vector<Edge_Condition>>&	get_edge_conditions() const;
		const std::vector<Action_Event>&									get_events() const;
		std::pair<std::string, std::string>									get_owner() const;
		std::string															get_name() const;
		Action create_action(std::string owner, const std::vector<std::string>& arguments, const Domain& domain) const;

	private:
		bool is_correct_type(const std::string& type, const std::string& object, const Domain& domain) const;
		std::unordered_map<std::string, std::vector<Agent>> get_condition_owner_to_agent(const Domain& domain, const std::unordered_map<std::string, std::string>& input_to_atom) const;

		std::string name;
		std::pair<std::string, std::string> owner;
		std::vector<Action_Event> events;
		std::vector<std::string> designated_events;
		std::vector<std::pair<std::string, std::string>> inputs;
		std::unordered_map<std::string, std::vector<Edge_Condition>> edge_conditions;
		// TODO - preconditions
	};
}