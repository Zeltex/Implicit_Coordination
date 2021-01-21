#pragma once

#include <string>
#include <unordered_set>
#include <unordered_map>
#include <map>

#include "Action_Event.hpp"
#include "Types.hpp"
#include "Agent.hpp"

namespace del {
	class Action;
	class Domain;
	class General_Action {
	public:
		General_Action() : cost((size_t) - 1), converter_generated(false) {}
		
		void add_edge_condition(Atom_Id agent, std::vector<Edge_Condition>&& edge_conditions);
		std::unordered_map<Proposition, Proposition> create_converter(const Domain& domain, const std::vector<Atom_Id>& arguments) const;
		void create_event(std::string name, Formula&& preconditions, const std::vector<Proposition>& add_list, const std::vector<Proposition>& delete_list);
		void set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs);
		void set_amount_of_agents(size_t amount_of_agents);
		void set_cost(size_t cost);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_instance_to_proposition(std::map<Proposition_Instance, Proposition>&& instance_to_proposition);
		void set_name(std::string name);
		void set_owner(std::string type, Atom_Id name);

		const std::unordered_map<Proposition, Proposition>&					get_converter() const;
		size_t																get_cost() const;
		const std::vector<std::string>&										get_designated_events() const;
		const std::unordered_map<size_t, std::vector<Edge_Condition>>&		get_edge_conditions() const;
		const std::vector<Action_Event>&									get_events() const;
		const std::vector<std::pair<std::string, std::string>>&				get_inputs() const;
		std::string															get_name() const;
		std::pair<std::string, Atom_Id>										get_owner() const;
		//Action create_action(Atom_Id owner, const std::vector<Atom_Id>& arguments, const Domain& domain) const;

		std::unordered_map<size_t, std::vector<Agent>> get_condition_owner_to_agent(const Domain& domain, const std::vector<Atom_Id>& arguments) const;
	private:

		size_t cost;
		std::string name;
		std::pair<std::string, Atom_Id> owner;
		std::vector<Action_Event> events;
		std::vector<std::string> designated_events;
		std::vector<std::pair<std::string, std::string>> inputs;
		std::unordered_map<size_t, std::vector<Edge_Condition>> edge_conditions;

		// Ids from input of general action to ids of propositions in formula
		std::map<Proposition_Instance, Proposition> input_to_formula;
		// Ids of propositinos in formula to ids in domain (grounded propositions)
		std::unordered_map<Proposition, Proposition> formula_to_domain;
		bool converter_generated;

		// TODO - preconditions
	};
}