#include "Domain_Interface_Implementation.h"

namespace del {
	void Domain_Interface_Implementation::new_domain(std::string name) {
		std::cout << "Starting domain" << std::endl;
		current_domain_name = name;
	}

	void Domain_Interface_Implementation::finish_domain() {
		std::cout << "Finishing domain" << std::endl;
	}

	void Domain_Interface_Implementation::new_action(std::string name) {
		current_action = General_Action();
		current_action.set_name(name);
	}

	void Domain_Interface_Implementation::finish_action() {
		std::cout << "Finishing action" << std::endl;
	}

	void Domain_Interface_Implementation::add_action_input(std::string type, std::string name) {
		std::cout << "Action input " << type << " " << name <<  std::endl;
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
}