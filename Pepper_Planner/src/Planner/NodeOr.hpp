#pragma once

#include "NodeBase.hpp"
#include "State.hpp"

#include <set>

namespace del
{
	class Action;
	class Agents;
	class NodeAnd;

	class NodeOr : public NodeBase
	{
		friend class NodeAnd;
	public:

		NodeOr(State state, Node_Id id, NodeAnd* parent);

		void add_child(NodeAnd* node, const Action* action);
		void add_parent(NodeAnd* node);
		const std::vector<std::pair<NodeAnd*, const Action*>>& get_children() const;
		std::vector<std::set<World_Id>> get_all_perspectives(const Agents* agents) const;
		std::optional<State> product_update(const Action* action, const Domain& domain, const std::set<World_Id>& designated_worlds) const;

		virtual void calculate_hash() override;
		virtual int calculate_value(std::deque<NodeBase*>& frontier) override;
		virtual bool check_if_dead() override;
		virtual bool check_if_solved() override;
		virtual void extract_policy(Policy& policy) override;
		size_t get_cost() const override;
		virtual bool is_goal(const Formula& goal_formula, const Domain& domain) const override;
		virtual bool is_leaf() const override;
		virtual void propagate_dead() override;
		virtual void propagate_solved() override;
		virtual std::string to_string(const Domain& domain) const override;
		virtual bool valuate(const Formula& formula, const Domain& domain) const override;
	private:
		State& get_state() override;
		const State& get_state() const override;

		State state;
		std::vector<NodeAnd*> parents;
		std::vector<std::pair<NodeAnd*, const Action*>> children;
	};
}