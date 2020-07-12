#include <string>
#include <iostream>
#include <fstream>

#include "Core.hpp"
#include "Graph.hpp"
#include "Domain.hpp"
#include "Policy.hpp"


namespace del {
	void print_graph(const Graph& graph, const Domain& domain) {
		std::ofstream myfile;
		myfile.open(DEBUG_PRINT_PATH + std::string("Graph.log"));
		myfile << graph.to_string(domain);
		myfile.close();
	}

	void print_graph_dot(const Graph& graph, const Domain& domain) {
		std::ofstream myfile;
		myfile.open(DEBUG_PRINT_PATH + std::string("Graph.dot"));
		myfile << graph.to_graph(domain);
		myfile.close();
	}

	void print_graph_dot_partial(const Graph& graph, const Domain& domain) {
		std::ofstream myfile;
		myfile.open(DEBUG_PRINT_PATH + std::string("Graph.dot"));
		myfile << graph.to_partial_graph(domain);
		myfile.close();
	}

	void print_action(const Action& action, const Domain& domain, size_t counter) {
		std::ofstream action_file;
		action_file.open(DEBUG_PRINT_PATH + std::string("dot/Action") + std::to_string(counter) + ".dot");
		action_file << "digraph G {\n" << action.to_graph("a", domain) << "}";
		action_file.close();
	}
	void print_state(const State& state, const Domain& domain, size_t counter) {
		std::ofstream state_file;
		state_file.open(DEBUG_PRINT_PATH + std::string("dot/State") + std::to_string(counter) + ".dot");
		state_file << "digraph {subgraph cluster_0 {" << state.to_graph("s0", domain) << "}}";
		state_file.close();
	}

	void clear_action_state_dir() {
		std::string command = "rm -r " + std::string(DEBUG_PRINT_PATH) + "dot/*";
		system(command.c_str());
		command = "rm -r " + std::string(DEBUG_PRINT_PATH) + "png/* 2> nul";
		system(command.c_str());
	}

	void print_policy(const Policy& policy, const Domain& domain) {
		std::ofstream state_file;
		state_file.open(std::string(DEBUG_PRINT_PATH) + "Policy.dot");
		state_file << "digraph {\ncompound = true;\n" << policy.to_graph(domain) << "}";
		state_file.close();
	}
}