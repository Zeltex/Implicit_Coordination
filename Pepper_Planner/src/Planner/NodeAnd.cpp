#include "NodeAnd.hpp"

#include "NodeOr.hpp"
#include "Policy.hpp"

#include <assert.h>

namespace del
{

	NodeAnd::NodeAnd(const State& state, Node_Id id)
		: state(state)
	{
		this->id = id;
		this->root = true;
	}

	NodeAnd::NodeAnd(const State& state, Node_Id id, NodeOr* parent)
		: state(state)
	{
		this->id = id;
		parents.push_back(parent);
	}

	void NodeAnd::add_parent(NodeOr* node)
	{
		parents.push_back(node);
	}

	void NodeAnd::add_child(NodeOr* node)
	{
		children.push_back(node);
	}

	const std::vector<NodeOr*>& NodeAnd::get_children() const
	{
		return children;
	}

	void NodeAnd::calculate_hash()
	{
		hash = get_state().to_hash();
	}

	bool NodeAnd::check_if_dead()
	{
		if (dead)
		{
			return true;
		}
		else if (solved)
		{
			return false;
		}

		for (NodeBase* child : children)
		{
			if (child->is_dead())
			{
				dead = true;
				return true;
			}
		}
		return false;
	}

	bool NodeAnd::check_if_solved()
	{
		if (solved)
		{
			return true;
		}
		else if (dead)
		{
			return false;
		}

		for (NodeBase* child : children)
		{
			if (!child->is_solved())
			{
				return false;
			}
		}
		solved = !children.empty();
		return solved;
	}

	int NodeAnd::calculate_value(std::deque<NodeBase*>& frontier)
	{
		if (value != UNKNOWN_VALUE)
		{
			return value;
		}

		if (children.empty())
		{
			value = 0;
		}
		else
		{
			int worst_value = EMPTY_VALUE;
			for (auto& child : children)
			{
				assert(child->is_solved());
				int temp_value = child->get_value();
				assert(temp_value != EMPTY_VALUE);

				if (temp_value == UNKNOWN_VALUE)
				{
					return value;
				}

				if (worst_value == EMPTY_VALUE || temp_value > worst_value)
				{
					worst_value = temp_value;
				}
			}

			value = worst_value;
		}

		// Enqueue parents
		for (auto& parent : parents)
		{
			if (!parent->is_solved())
			{
				continue;
			}

			frontier.push_back(parent);
		}

		return value;
	}

	void NodeAnd::extract_policy(Policy& policy)
	{
		assert(value != EMPTY_VALUE && value != UNKNOWN_VALUE);

		for (NodeBase* child : children)
		{
			assert(child->is_solved());

			if (!policy.try_visit(child))
			{
				continue;
			}

			child->extract_policy(policy);
		}
	}

	void NodeAnd::propagate_dead()
	{
		if (solved || dead || !check_if_dead())
		{
			return;
		}

		for (NodeOr* parent : parents)
		{
			parent->propagate_dead();
		}
	}
	
	void NodeAnd::propagate_solved()
	{
		if (solved || dead || !check_if_solved())
		{
			return;
		}

		for (NodeOr* parent : parents)
		{
			parent->propagate_solved();
		}
	}

	size_t NodeAnd::get_cost() const
	{
		return state.get_cost();
	}

	State& NodeAnd::get_state()
	{
		return state;
	}

	const State& NodeAnd::get_state() const
	{
		return state;
	}

	bool NodeAnd::is_goal(const Formula& goal_formula, const Domain& domain) const
	{
		return state.valuate(goal_formula, domain);
	}

	bool NodeAnd::is_leaf() const
	{
		return children.empty();
	}

	std::string NodeAnd::to_string(const Domain& domain) const
	{
		return "";
	}

	bool NodeAnd::valuate(const Formula& formula, const Domain& domain) const
	{
		return state.valuate(formula, domain);
	}
}