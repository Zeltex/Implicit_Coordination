#include "NodeOr.hpp"

#include "Action.hpp"
#include "Agents.hpp"
#include "Graph.hpp"
#include "NodeAnd.hpp"
#include "Policy.hpp"
#include "State.hpp"

#include <assert.h>


namespace del
{
	NodeOr::NodeOr(State state, Node_Id id, NodeAnd* parent)
		: state(std::move(state))
	{
		this->id = id;
		parents.push_back(parent);
	}

	void NodeOr::add_parent(NodeAnd* node)
	{
		parents.push_back(node);
	}

	void NodeOr::calculate_hash()
	{
		hash = get_state().to_hash();
	}

	std::optional<State> NodeOr::product_update(const Action* action, const Domain& domain, const std::set<World_Id>& designated_worlds) const
	{
		return get_state().product_update(action, domain, designated_worlds);
	}

	std::vector<std::set<World_Id>> NodeOr::get_all_perspectives(const Agents* agents) const
	{
		std::vector<std::set<World_Id>> result;
		const State& state = get_state();
		auto designated_world = *state.get_designated_worlds().begin();
		for (auto& agent : *agents)
		{
			result.emplace_back(std::move(state.get_reachable_worlds(&agent, designated_world)));
		}
		return result;
	}

	bool NodeOr::check_if_dead()
	{
		if (dead)
		{
			return true;
		}
		else if (solved)
		{
			return false;
		}

		for (auto& [child, action] : children)
		{
			if (!child->is_dead())
			{
				return false;
			}
		}
		dead = true;
		return true;
	}

	bool NodeOr::check_if_solved()
	{
		if (solved)
		{
			return true;
		}
		else if (dead)
		{
			return false;
		}

		for (auto& [child, action] : children)
		{
			if (child->is_solved())
			{
				solved = true;
				return true;
			}
		}
		return false;
	}

	int NodeOr::calculate_value(std::deque<NodeBase*>& frontier)
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
			bool found_unknown = false;
			int best_value = EMPTY_VALUE;
			for (auto& [child, action] : children)
			{
				if (!child->is_solved())
				{
					continue;
				}

				int temp_value = child->get_value();

				if (temp_value == EMPTY_VALUE)
				{
					continue;
				}

				if (temp_value == UNKNOWN_VALUE)
				{
					found_unknown = true;
					continue;
				}

				temp_value += (int)action->get_cost();

				if (best_value == EMPTY_VALUE || temp_value < best_value)
				{
					best_value = temp_value;
				}
			}

			if (best_value == EMPTY_VALUE)
			{	
				// At least one child is indetermined
				if (found_unknown)
				{
					return UNKNOWN_VALUE;
				}
				// No children with value
				else
				{
					value = EMPTY_VALUE;
					return value;
				}

			}

			value = best_value;
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

	void NodeOr::extract_policy(Policy& policy)
	{
		assert(value != EMPTY_VALUE && value != UNKNOWN_VALUE);

		if (children.empty())
		{
			assert(solved);
			return;
		}

		for (auto& [child, action] : children)
		{
			if (!child->is_solved())
			{
				continue;
			}
			
			if (child->get_value() + action->get_cost() != value)
			{
				continue;
			}

			policy.add_entry(get_state(), action, this);

			return child->extract_policy(policy);
		}

		assert(false);

	}

	void NodeOr::propagate_dead()
	{
		if (solved || dead || !check_if_dead())
		{
			return;
		}

		for (NodeAnd* parent : parents)
		{
			parent->propagate_dead();
		}
	}

	void NodeOr::propagate_solved()
	{
		if (solved || dead || !check_if_solved())
		{
			return;
		}

		for (NodeAnd* parent : parents)
		{
			parent->propagate_solved();
		}
	}

	void NodeOr::add_child(NodeAnd* node, const Action* action)
	{
		children.push_back({ node, action });
	}

	const std::vector<std::pair<NodeAnd*, const Action*>>& NodeOr::get_children() const
	{
		return children;
	}

	size_t NodeOr::get_cost() const
	{
		return get_state().get_cost();
	}

	const State& NodeOr::get_state() const
	{
		return state;
	}

	State& NodeOr::get_state()
	{
		return state;
	}

	bool NodeOr::is_goal(const Formula& goal_formula, const Domain& domain) const
	{
		return valuate(goal_formula, domain);
	}

	bool NodeOr::is_leaf() const
	{
		return children.empty();
	}

	std::string NodeOr::to_string() const
	{
		std::string result = "Node OR " + id.to_string() + "\nParents ";
		for (auto& parent : parents)
		{
			result += parent->get_id().to_string() + " ";
		}

		result += "\nChildren ";

		for (auto& [child, action]: children)
		{
			result += "(" + child->get_id().to_string() + " " + action->to_string() + ") ";
		}

		result += "\n";

		if (solved)
		{
			result += "Solved";
		}
		else if (dead)
		{
			result += "Dead";
		}
		else
		{
			result += "Unknown";
		}


		return result + "\n" + state.to_string();
	}

	bool NodeOr::valuate(const Formula& formula, const Domain& domain) const
	{
		return get_state().valuate(formula, domain);
	}
}