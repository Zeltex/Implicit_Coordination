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
		General_Action() : cost((size_t) - 1) {}
		void set_cost(size_t cost);
		void set_owner(std::string type, Atom_Id name);
		void set_name(std::string name);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_action_input(std::vector<std::pair<std::string, Atom_Id>> inputs);
		void create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list);
		void set_amount_of_agents(size_t amount_of_agents);
		void add_edge_condition(Atom_Id agent, std::vector<Edge_Condition>&& edge_conditions);

		size_t																get_cost() const;
		const std::vector<std::pair<std::string, Atom_Id>>&					get_inputs() const;
		const std::vector<std::string>&										get_designated_events() const;
		const std::unordered_map<size_t, std::vector<Edge_Condition>>&		get_edge_conditions() const;
		const std::vector<Action_Event>&									get_events() const;
		std::pair<std::string, Atom_Id>										get_owner() const;
		std::string															get_name() const;
		Action create_action(Atom_Id owner, const std::vector<Atom_Id>& arguments, const Domain& domain) const;

	private:
		bool is_correct_type(const std::string& type, const Atom_Id& object, const Domain& domain) const;
		std::unordered_map<size_t, std::vector<Agent>> get_condition_owner_to_agent(const Domain& domain, const std::unordered_map<size_t, Atom_Id>& input_to_atom) const;

		size_t cost;
		std::string name;
		std::pair<std::string, Atom_Id> owner;
		std::vector<Action_Event> events;
		std::vector<std::string> designated_events;
		std::vector<std::pair<std::string, Atom_Id>> inputs;
		std::unordered_map<size_t, std::vector<Edge_Condition>> edge_conditions;
		// TODO - preconditions
	};
}