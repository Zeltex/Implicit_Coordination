#pragma once

#include <vector>
#include <tuple>

#include "State.hpp"
#include "Action.hpp"
#include "Misc.hpp"
#include "DEL_Operations.hpp"

namespace del {
	class Node_Comparator;
	struct Policy_Entry {
		State state;
		std::vector<std::pair<Action, Node_Id>> actions;
	};
	class Policy {
	public:

		Policy(bool solved) : solved(solved) {}

		void add_entry(const State& state, const Action& action, const Node_Id& node_id);
		bool is_solved() const;
		std::optional<Action> get_action(const State& state, Agent_Id preferred_agent = { 0 }) const;

		std::string to_graph(const Domain& domain) const;
		std::string to_string(const Domain& domain) const;
	private:
		bool solved;
		std::unordered_map<size_t, Policy_Entry> policy;
	};
}