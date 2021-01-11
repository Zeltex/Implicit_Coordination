#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "Domain_Interface.hpp"
#include "Loader_Types.hpp"
#include "General_Action.hpp"
#include "General_World.hpp"
#include "Domain.hpp"
#include "Action_Library.hpp"

namespace del {

	class Domain_Interface_Implementation : public Domain_Interface {
	public:
		Domain_Interface_Implementation(): 
			actions(), current_action(), initial_state(), library(), domain(), propositions(), world_name_to_id(), action_reflexivity(false){}
		virtual void new_domain(std::string name) override;
		virtual void finish_domain() override;
		virtual void finish_problem() override;
		virtual void new_action(std::string name) override;
		virtual void finish_action() override;


		virtual void set_action_cost(size_t cost) override;
		virtual void set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) override;
		virtual void set_action_owner(std::string type, std::string name, Atom_Id id) override;
		virtual void set_announce_enabled() override;
		virtual void set_designated_events(std::vector<std::string> designated_events) override;
		virtual void set_designated_worlds(const std::unordered_set<std::string>& designated_worlds) override;
		virtual void set_domain(std::string domain_name) override;
		virtual void set_goal(del::Formula&& goal, const std::unordered_map<std::string, Atom_Id>& atom_to_id) override;
		virtual void set_initial_propositions(const std::vector<Proposition_Instance>& propositions, const std::unordered_map<std::string, Atom_Id>& atom_to_id) override;
		virtual void set_objects(std::unordered_map<std::string, std::unordered_set<std::string>>&& objects) override;
		virtual void set_types(const std::unordered_set<std::string>& types) override;


		virtual void create_event(std::string name, del::Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list) override;
		virtual void create_world(std::string name, const std::vector<Proposition_Instance>& propositions, const std::unordered_map<std::string, Atom_Id>& atom_to_id) override;
		virtual void create_action_reflexive_reachables() override;
		virtual void create_state_reflexive_reachables() override;

		virtual void add_observability(std::string observer, const std::vector<std::string>& agents) override;
		virtual void add_edge_condition(Atom_Id agent, std::vector< std::tuple<std::string, std::string, del::Formula>>&& edge_conditions) override;
		virtual void add_perceivability(std::string perceiver, const std::vector<std::string>& agents) override;
		virtual void add_proposition(std::string name, const std::vector<std::pair<std::string, std::string>>& inputs) override;
		virtual void add_reachability(std::string name, const std::vector<std::pair<std::string, std::string>>& reachables) override;
		std::tuple<Domain, Action_Library, Formula> get_loaded();
	private:
		std::vector<General_Action> actions;
		General_Action current_action;
		State initial_state;
		Action_Library library;
		Domain domain;
		Formula goal;
		bool action_reflexivity;
		std::vector<Proposition> propositions;
		std::unordered_map<std::string, World_Id> world_name_to_id;
		std::unordered_map<std::string, std::vector<std::string>> observability;
		std::unordered_map<std::string, std::vector<std::string>> perceivability;

		std::unordered_map<std::string, Atom_Id> atom_to_id;
	};
}