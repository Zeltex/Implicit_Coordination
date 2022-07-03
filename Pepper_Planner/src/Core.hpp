#pragma once
namespace del {

#ifdef EXPORT_TEST_FUNCTIONS

#define UNITTESTAPP_EXPORT __declspec(dllexport)
#else
#define UNITTESTAPP_EXPORT
#endif

#if 0
#define BISIMILAR_USE_HASH_ENABLED 1
#define REMOVE_UNREACHABLE_WORLDS_ENABLED 1
#define BISIM_COMPARISON_ENABLED 1
#define BISIM_CONTRACTION_ENABLED 1
#define DEBUG_PRINT 1
#define PRINT_PARTIAL 1
#endif

// Planner options
#ifndef BISIMILAR_USE_HASH_ENABLED
#define BISIMILAR_USE_HASH_ENABLED 1
#endif
#ifndef REMOVE_UNREACHABLE_WORLDS_ENABLED
#define REMOVE_UNREACHABLE_WORLDS_ENABLED 1
#endif
#ifndef BISIM_COMPARISON_ENABLED 
#define BISIM_COMPARISON_ENABLED 1
#endif
#ifndef BISIM_CONTRACTION_ENABLED
#define BISIM_CONTRACTION_ENABLED 1
#endif
#ifndef OPR_ENABLED
#define OPR_ENABLED 1
#endif
#ifndef DEBUG_PRINT 
#define DEBUG_PRINT 0
#endif
#ifndef PRINT_PARTIAL
#define PRINT_PARTIAL 0
#endif
#ifndef PRINT_NODES
#define PRINT_NODES 1
#endif

#define PERCEIVES "perceives"
#define OBSERVES "observes"
#define ANNOUNCE_COST 100
#define ANNOUNCE_NAME "Announce"
#define BISIMILAR_DEPTH 5

#ifndef DEBUG_PRINT_PATH
#define DEBUG_PRINT_PATH "../Debug_Output/"
#endif


#if DEBUG_PRINT == 1

	class Action;
	class Domain;
	
	void print_action_to_console(const Action& action, const Domain& domain);
	#define PRINT_ACTION_TO_CONSOLE(action, domain) print_action_to_console(action, domain)
#else
	#define PRINT_ACTION_TO_CONSOLE(action, domain)
#endif
}
