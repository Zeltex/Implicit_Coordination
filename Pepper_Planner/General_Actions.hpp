#pragma once

#include <map>
#include <string>

#include "Agents.hpp"
#include "General_Action_Events.hpp"
#include "General_Edge_Conditions.hpp"
#include "Types.hpp"
#include "Proposition_Instance.hpp"
#include "Inputs_Buffer.hpp"

namespace del {
	class Action;
	class Atoms;
	class Domain;
	class General_Domain;
	class Propositions_Lookup;
	class Variables_Buffer;

	class General_Action {
		friend class General_Actions;
	public:
		General_Action() : cost((size_t) - 1), converter_generated(false) {}
		General_Action(const std::string& name);
		
		std::map<Proposition, Proposition> create_converter(const Propositions_Lookup& propositions_Lookup, const Atoms& arguments) const;
		void set_cost(size_t cost);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions);
		void set_instance_to_proposition(std::map<Proposition_Instance, Proposition> instance_to_proposition);
		void set_name(std::string name);
		void set_owner(std::string type, Atom_Id name);

		const Inputs& get_inputs() const;

		size_t														get_cost() const;
		const std::vector<std::string>&								get_designated_events() const;
		const General_Agent_Edge_Conditions&						get_edge_conditions() const;
		const General_Action_Events&								get_events() const;
		std::string													get_name() const;
		std::pair<std::string, Atom_Id>								get_owner() const;

	private:

		size_t cost;
		std::string name;
		std::pair<std::string, Atom_Id> owner;
		General_Action_Events events;
		std::vector<std::string> designated_events;
		Inputs inputs;
		General_Agent_Edge_Conditions edge_conditions;

		// Ids from input of general action to ids of propositions in formula
		std::map<Proposition_Instance, Proposition> input_to_formula;
		// Ids of propositinos in formula to ids in domain (grounded propositions)
		std::map<Proposition, Proposition> formula_to_domain;
		bool converter_generated;

	};

	class General_Actions 
	{
	public:
		void start(const std::string name);
		void set_input(Inputs_Buffer& inputs_buffer);
		void set_owner(const std::string type, const std::string name);
		void set_designated_events(Variables_Buffer& variables_buffer);
		void set_cost(size_t cost);
		void set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions);

		const Inputs& get_inputs() const;
		std::vector<General_Action>::const_iterator begin() const;
		std::vector<General_Action>::const_iterator end() const;
	private:
		std::vector<General_Action> actions;
	};
}