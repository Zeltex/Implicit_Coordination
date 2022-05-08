#include <string>
#include <iostream>
#include <fstream>
#include <set>

#include "Core.hpp"
#include "Graph.hpp"
#include "Domain.hpp"
#include "Policy.hpp"


namespace del {

	void print_action_to_console(const Action& action, const Domain& domain) 
	{
		std::cout << "Performed action " << action.get_name() << " (" ;
		if (action.get_name() == ANNOUNCE_NAME) 
		{
			std::cout << action.get_events().get_first_event().get_preconditions().to_string(domain);
		} 
		else 
		{
			std::cout << action.args.to_string(domain) << ")";
		}
		std::cout << "\n";
	}
}