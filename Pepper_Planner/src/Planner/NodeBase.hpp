#pragma once

#define EMPTY_VALUE -1
#define UNKNOWN_VALUE -2

#include "Types.hpp"

#include <vector>
#include <deque>

namespace del 
{
	class Domain;
	class Formula;
	class Policy;

	class NodeBase
	{
	public:
		virtual ~NodeBase() {}

		virtual int calculate_value(std::deque<NodeBase*>& frontier) = 0;
		virtual void calculate_hash() = 0;
		virtual bool check_if_dead() = 0;
		virtual bool check_if_solved() = 0;
		virtual void extract_policy(Policy& policy) = 0;
		virtual size_t get_cost() const = 0;

		virtual bool is_goal(const Formula& goal_formula, const Domain& domain) const = 0;
		virtual bool is_leaf() const = 0;
		virtual void propagate_dead() = 0;
		virtual void propagate_solved() = 0;
		virtual std::string to_string(const Domain& domain) const = 0;
		virtual bool valuate(const Formula& formula, const Domain& domain) const = 0;

		void set_dead();
		void set_solved();
		size_t get_hash() const;
		Node_Id	get_id() const;
		int get_value() const;
		bool has_value() const;
		bool is_root_node() const;
		bool is_dead() const;
		bool is_solved() const;
	
	protected:

		virtual State& get_state() = 0;
		virtual const State& get_state() const = 0;

		Node_Id id;
		bool root;
		bool dead;
		bool solved;
		size_t hash = EMPTY_INDEX;
		int value = UNKNOWN_VALUE;
	};
}