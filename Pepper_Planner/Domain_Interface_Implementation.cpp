#include "Domain_Interface_Implementation.h"

namespace del {
	void Domain_Interface_Implementation::set_debug_working() {
		working = true;
	}

	void Domain_Interface_Implementation::new_domain(std::string name) {
		std::cout << "Starting domain" << std::endl;
		current_domain_name = name;
	}

	void Domain_Interface_Implementation::finish_domain() {
		std::cout << "Finishing domain" << std::endl;
	}

	void Domain_Interface_Implementation::new_action(std::string name) {
		std::cout << "Starting action" << std::endl;
	}

	void Domain_Interface_Implementation::finish_action() {
		std::cout << "Finishing action" << std::endl;
	}

	void Domain_Interface_Implementation::add_action_input(std::string type, std::string name) {
		std::cout << "Action input " << type << " " << name <<  std::endl;
	}

	void Domain_Interface_Implementation::set_action_owner(std::string name) {
		std::cout << "Action owner " << name << std::endl;
	}

	void Domain_Interface_Implementation::new_action_preconditions() {
		std::cout << "Action preconditions start " << std::endl;
	}
	void Domain_Interface_Implementation::finish_action_preconditions() {
		std::cout << "Action preconditions end " << std::endl;
	}

	void Domain_Interface_Implementation::new_event(std::string name) {
		std::cout << "Starting event" << std::endl;
	}

	void Domain_Interface_Implementation::finish_event() {
		std::cout << "Finishing event" << std::endl;
	}

	void Domain_Interface_Implementation::start_preconditions() {
		std::cout << "Starting preconditions" << std::endl;
	}

	void Domain_Interface_Implementation::finish_preconditions() {
		std::cout << "Finishing preconditions" << std::endl;
	}

	void Domain_Interface_Implementation::start_delete_list() {
		std::cout << "starting delete list" << std::endl;
	}

	void Domain_Interface_Implementation::finish_delete_list() {
		std::cout << "Finishing delete list" << std::endl;
	}

	void Domain_Interface_Implementation::start_add_list() {
		std::cout << "starting add list" << std::endl;
	}

	void Domain_Interface_Implementation::finish_add_list() {
		std::cout << "Finishing add list" << std::endl;
	}

}