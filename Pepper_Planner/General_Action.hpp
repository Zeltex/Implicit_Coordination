#pragma once

#include <string>
#include <unordered_set>

#include "Action_Event.hpp"

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
		void add_reachability_relation(Agent_Id agent, Event_Id from, Event_Id to);
		void set_amount_of_agents(size_t amount_of_agents);

		const std::vector<std::vector<Event_Relation>>& get_reachability_relations() const;
		const std::vector<std::pair<std::string, std::string>>& get_inputs() const;
		const std::vector<std::string>& get_designated_events() const;
		const std::vector<Action_Event>& get_events() const;
		std::pair<std::string, std::string>  get_owner() const;
		std::string get_name() const;
		Action create_action(std::string owner, const std::vector<std::string>& arguments, const Domain& domain) const;

	private:

		std::string name;
		std::pair<std::string, std::string> owner;
		std::vector<Action_Event> events;
		std::vector<std::string> designated_events;
		std::vector<std::pair<std::string, std::string>> inputs;
		std::vector<std::vector<Event_Relation>> reachability_relation;
		// TODO - preconditions
	};
}