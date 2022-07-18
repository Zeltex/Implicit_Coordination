#pragma once
#include "Action.hpp"

#include <iostream>

namespace del {

#ifndef DEBUG_PRINT 
#define DEBUG_PRINT 0
#endif
#ifndef PRINT_PARTIAL
#define PRINT_PARTIAL 0
#endif
#ifndef PRINT_NODES
#define PRINT_NODES 1
#endif

#if DEBUG_PRINT == 1

	class Action;
	class Domain;
	
	void print_action_to_console(const Action& action);
	#define PRINT_ACTION_TO_CONSOLE(action) std::cout << action->to_string() << std::endl;
	#define PRINT(msg) std::cout << msg << std::endl;
#else
	#define PRINT_ACTION_TO_CONSOLE(action)
	#define PRINT(msg)
#endif
}
