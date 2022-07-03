#pragma once

#include <vector>
#include <tuple>

#include "State.hpp"
#include "Action.hpp"
#include "Misc.hpp"

namespace del {
	class Node_Comparator;
	struct Policy_Entry {
		State state;
		std::vector<std::pair<const Action*, const Node*>> actions;
	};
	class Policy {
	public:

		Policy(bool solved) : solved(solved) {}

		void add_entry(const State& state, const Action* action, const Node* node);
		bool is_solved() const;
		const Action* get_action(const State& state, Agent_Id preferred_agent = { 0 }) const;

		std::string to_string(const Domain& domain) const;
	private:
		bool solved;
		std::unordered_map<size_t, Policy_Entry> policy;
	};
}