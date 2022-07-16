#pragma once

#include <vector>
#include <tuple>

#include "State.hpp"
#include "Action.hpp"
#include "Misc.hpp"

namespace del {
	class Agents;
	class Node_Comparator;
	class NodeBase;

	struct Policy_Entry {
		State state;
		std::vector<std::pair<const Action*, const NodeBase*>> actions;
	};
	class Policy {
	public:

		Policy(bool solved) : solved(solved) {}

		void add_entry(const State& state, const Action* action, const NodeBase* node);
		bool is_solved() const;
		const Action* get_action(const State& state, const Agents* agents, Agent_Id preferred_agent = { 0 }) const;
		bool try_visit(NodeBase* node);

		std::string to_string(const Domain& domain) const;
	private:
		bool solved;
		std::unordered_map<size_t, Policy_Entry> policy;
		std::unordered_set<NodeBase*> visited;
	};
}