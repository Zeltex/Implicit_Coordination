#include "Domain_Interface_Implementation.h"

namespace del {
	void Domain_Interface_Implementation::new_domain(std::string name) {
		std::cout << "Starting domain" << std::endl;
		current_domain_name = name;
	}

	void Domain_Interface_Implementation::finish_domain() {
		std::cout << "Finishing domain" << std::endl;
	}

	void Domain_Interface_Implementation::finish_problem() {
		std::cout << "Finishing problem" << std::endl;
	}

	void Domain_Interface_Implementation::new_action(std::string name) {
		current_action = General_Action();
		current_action.set_name(name);
	}

	void Domain_Interface_Implementation::finish_action() {
		std::cout << "Finishing action" << std::endl;
	}

	void Domain_Interface_Implementation::set_action_input(std::vector<std::pair<std::string, std::string>> inputs) {
		current_action.set_action_input(inputs);
	}

	void Domain_Interface_Implementation::set_action_owner(std::string name) {
		std::cout << "Action owner " << name << std::endl;
		current_action.set_owner(name);
	}

	void Domain_Interface_Implementation::create_event(std::string name, Formula&& preconditions, std::unordered_set<std::string> add_list, std::unordered_set<std::string> delete_list) {
		current_action.create_event(name, std::move(preconditions), add_list, delete_list);
	}


	void Domain_Interface_Implementation::set_designated_events(std::vector<std::string> designated_events) {
		current_action.set_designated_events(designated_events);
	}

	void Domain_Interface_Implementation::set_types(std::unordered_set<std::string> types) {
		this->types = types;
	}

	void Domain_Interface_Implementation::add_proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) {
		propositions.emplace_back(name, inputs);
	}

	void Domain_Interface_Implementation::set_objects(std::unordered_map<std::string, std::unordered_set<std::string>> objects) {
		this->objects = objects;
	}

	void Domain_Interface_Implementation::set_domain(std::string domain_name) {
		this->domain_name = domain_name;
	}

	void Domain_Interface_Implementation::set_initial_state(std::vector<Proposition_Instance> propositions) {
		this->initial_state = propositions;
	}

	void Domain_Interface_Implementation::create_world(std::string name, std::vector<Proposition_Instance> propositions) {
		this->worlds.emplace_back(name, propositions);
	}

	void Domain_Interface_Implementation::set_designated_worlds(std::unordered_set<std::string> designated_worlds) {
		this->designated_worlds = designated_worlds;
	}

	void Domain_Interface_Implementation::create_reflexive_reachables() {
		//TODO
		int debug = 0;
	}

	void Domain_Interface_Implementation::add_reachability(std::string name, std::vector<std::pair<std::string, std::string>> reachables) {
		this->reachables[name] = reachables;
	}
}