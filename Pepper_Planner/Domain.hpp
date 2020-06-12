#pragma once

#include <vector>

#include "Node.hpp"
#include "Action.hpp"
#include "State.hpp"
#include "DEL.hpp"
#include "Agent.hpp"

namespace del {

	class Domain {
	public:
		void find_policy();
	private:
		Node get_next_from_frontier(std::vector<Node> frontier);
		void extract_policy();
		void propogate_dead_end_node(Node& node);
		bool is_goal_node(Node& node);
		bool is_root_node(Node& node);
		bool is_valid_state(State state);
		std::vector<Action> get_all_actions();
		std::vector<Agent> get_all_agents();
	};
}