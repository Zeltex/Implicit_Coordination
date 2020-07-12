#pragma once
namespace del {

#define PERCEIVES "perceives"
#define OBSERVES "observes"

#ifndef DEBUG_PRINT_PATH
#define DEBUG_PRINT_PATH "../Debug_Output/"
#endif


#ifdef DEBUG_PRINT

	class Action;
	class Agent;
	class Domain;
	class Graph;
	class Policy;
	class State;

	void print_graph_dot(const Graph& graph, const Domain& domain);
	void print_graph_dot_partial(const Graph& graph, const Domain& domain);
	void print_graph(const Graph& graph, const Domain& domain);
	void print_action(const Action& action, const Domain& domain, size_t counter);
	void print_state(const State& state, const Domain& domain, size_t counter);
	void clear_action_state_dir();
	void print_policy(const Policy& policy, const Domain& domain);

	#define PRINT_POLICY(policy, domain) print_policy(policy, domain)
	#define PRINT_GRAPH(graph, domain) print_graph(graph,domain)
	#define PRINT_ACTION(action, domain, counter) print_action(action, domain, counter)
	#define PRINT_STATE(state, domain, counter) print_state(state, domain, counter)
	#define CLEAR_ACTION_STATE_DIR() clear_action_state_dir()

	#ifdef PRINT_PARTIAL
		#define PRINT_GRAPH_DOT(graph, domain) print_graph_dot_partial(graph,domain)
	#else
		#define PRINT_GRAPH_DOT(graph, domain) print_graph_dot(graph,domain)
	#endif
#else
	#define PRINT_ACTION(action, domain, counter) 
	#define PRINT_STATE(state, domain, counter)
	#define PRINT_GRAPH_DOT(graph, domain)
	#define PRINT_GRAPH(graph, domain)
	#define CLEAR_ACTION_STATE_DIR()
#endif
}