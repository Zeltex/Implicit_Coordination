#include <string>
#include <iostream>
#include <fstream>
#include <set>

#include "Core.hpp"
#include "Graph.hpp"
#include "Domain.hpp"
#include "Policy.hpp"


namespace del {

	void print_action_to_console(const Action& action, const Domain& domain) {
		std::cout << "Performed action " << action.get_name() << " (" ;
		if (action.get_name() == ANNOUNCE_NAME) {
			std::cout << action.get_events().get_first_event().get_preconditions().to_string(domain.get_id_to_atom());
		} else {
			std::set<size_t> arg_set;
			for (auto& entry : action.args) {
				std::cout << domain.get_atom_name(entry) << " ";
			}
			std::cout << ")";
		}
		std::cout << "\n";
	}
}