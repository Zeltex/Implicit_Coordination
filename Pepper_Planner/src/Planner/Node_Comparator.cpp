#include "Node_Comparator.hpp"

#include "Action.hpp"
#include "State.hpp"
#include "NodeAnd.hpp"
#include "NodeOr.hpp"
#include "Core.hpp"

#include <assert.h>

namespace del {

	Node_Comparator::Node_Comparator(NodeAnd* root_node) 
	{
		insert(root_node);
	}

	bool Node_Comparator::does_bisimilar_exist(const State& state, NodeOr* parent, const Action* action) const
	{
		auto hash = state.to_hash();
		auto match = visited_and.find(hash);

		if (match == visited_and.end())
		{
			return false;
		}

		match->second->add_parent(parent);
		parent->add_child(match->second, action);
		return true;
	}

	bool Node_Comparator::does_bisimilar_exist(const State& state, NodeAnd* parent) const
	{
		auto hash = state.to_hash();
		auto match = visited_or.find(hash);

		if (match == visited_or.end())
		{
			return false;
		}

		match->second->add_parent(parent);
		parent->add_child(match->second);
		return true;
	}

	void Node_Comparator::insert(NodeAnd* node)
	{
		auto hash = node->get_hash();
		assert(visited_and.find(hash) == visited_and.end());
		visited_and.insert({ hash, node });
	}

	void Node_Comparator::insert(NodeOr* node)
	{
		auto hash = node->get_hash();
		assert(visited_or.find(hash) == visited_or.end());
		visited_or.insert({ hash, node });
	}
}