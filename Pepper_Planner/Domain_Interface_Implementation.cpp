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
}