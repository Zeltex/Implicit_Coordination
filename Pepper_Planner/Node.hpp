#pragma once

#include <vector>

#include "State.hpp"
#include "Types.hpp"
#include "Formula.hpp"
#include "Action.hpp"

namespace del {
	class Graph;
	class Node {

	public:
		Node() = delete;
		Node(State state, Node_Id id, Node* parent, Action action_from_parent, bool root);
		Node(State state, Node_Id id, Node* parent, bool root);
		void add_child(Node* node);
		void add_parent(Node* node, const Action& action);
		void add_parent(Node* node);
		void calculate_hash();
		void set_dead();
		void set_solved();

		const std::vector<Node*>&						get_children() const;
		size_t											get_cost() const;
		size_t											get_hash() const;
		Node_Id											get_id() const;
		const Action&									get_parent_action(Node* parent) const;
		const std::vector<std::pair<Node*, Action>>&	get_parents() const;
		const State&									get_state()const ;
		Node_Type										get_type() const;

		bool is_root_node() const;
		bool is_dead() const;
		bool is_solved() const;
		bool is_goal(const Formula& goal_formula, const Domain& domain) const;
		bool check_if_dead();
		bool check_if_solved();
		bool valuate(const Formula& formula, const Domain& domain) const;
		
		std::string to_string(const Domain& domain) const;
		std::string type_to_string() const;

	private:

		bool check_if_dead_and();
		bool check_if_dead_or();
		bool check_if_solved_and();
		bool check_if_solved_or();

		Node_Type type;
		State state;
		Node_Id id;
		std::vector<std::pair<Node*, Action>> parents;
		bool root;
		bool dead;
		bool solved;
		std::vector<Node*> children;
		size_t hash;
	};
}