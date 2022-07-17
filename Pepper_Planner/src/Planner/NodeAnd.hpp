#pragma once

#include "NodeBase.hpp"

#include "State.hpp"

namespace del
{
	class NodeOr;
	class Policy;

	class NodeAnd : public NodeBase
	{
		friend class NodeOr;
	public:
		NodeAnd(const State& state, Node_Id id);
		NodeAnd(const State& state, Node_Id id, NodeOr* parent);

		void add_child(NodeOr* node);
		void add_parent(NodeOr* node);
		const std::vector<NodeOr*>& get_children() const;

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
		virtual std::string to_string() const override;
		virtual bool valuate(const Formula& formula, const Domain& domain) const override;

	private:
		State& get_state() override;
		const State& get_state() const override;
		
		State state;
		std::vector<NodeOr*> children;
		std::vector<NodeOr*> parents;
	};
}