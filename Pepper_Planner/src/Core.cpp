#include <string>
#include <iostream>
#include <fstream>
#include <set>

#include "Action.hpp"
#include "Core.hpp"
#include "Domain.hpp"

namespace del {

	void print_action_to_console(const Action& action) 
	{
		std::cout << "Performed " ;
		if (action.get_name() == ANNOUNCE_NAME) 
		{
			std::cout << action.get_events().get_first_event().get_preconditions().to_string();
		} 
		else 
		{
			std::cout << action.to_string();
		}
		std::cout << "\n";
	}
}