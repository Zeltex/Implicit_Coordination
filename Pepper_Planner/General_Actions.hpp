#pragma once

#include <map>
#include <string>

#include "Agents.hpp"
#include "General_Action_Events.hpp"
#include "General_Edge_Conditions.hpp"
#include "Inputs_Buffer.hpp"
#include "Proposition_Instance.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "Types.hpp"

namespace del {
	class Action;
	class Atoms;
	class Atom_Arguments;
	class Domain;
	class General_Domain;
	class Propositions_Lookup;
	class Variables_Buffer;

	class General_Action {
		friend class General_Actions;
	public:
		General_Action() : cost((size_t) - 1) {}
		General_Action(const std::string& name);
		
		std::map<Proposition, Proposition> create_converter(const Propositions_Lookup& propositions_Lookup, const Atoms& arguments) const;
		std::map<Proposition, Proposition> create_converter(const Propositions_Lookup& propositions_Lookup, const Atom_Arguments& arguments) const;
		void set_cost(size_t cost);
		void set_designated_events(std::vector<std::string> designated_events);
		void set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions);
		void set_events(General_Action_Events& general_action_events);
		void set_name(std::string name);
		void set_owner(std::string type, Atom_Id name);
		void set_propositions_buffer(Proposition_Instance_Buffer& proposition_instance_buffer);

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
		Proposition_Instance_Buffer proposition_instance_buffer;
	};

	class General_Actions 
	{
	public:
		void start(const std::string name);
		void set_cost(size_t cost);
		void set_designated_events(Variables_Buffer& variables_buffer);
		void set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions);
		void set_events(General_Action_Events& general_action_events);
		void set_input(Inputs_Buffer& inputs_buffer);
		void set_owner(const std::string type, const std::string name);
		void set_propositions_buffer(Proposition_Instance_Buffer& proposition_instance_buffer);

		const Inputs& get_inputs() const;
		std::vector<General_Action>::const_iterator begin() const;
		std::vector<General_Action>::const_iterator end() const;
	private:
		std::vector<General_Action> actions;
	};
}