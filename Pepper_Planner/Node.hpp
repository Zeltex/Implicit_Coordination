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
		Node(State state, Node_Id id, Node_Id parent, Action action_from_parent, bool root) :
			state(state), id(id), parents({ {parent, action_from_parent } }), root(root), type(Node_Type::And),
			dead(false), solved(false), hash(0) {};
		// TODO - Don't create dummy action (though it won't get used)
		Node(State state, Node_Id id, Node_Id parent, bool root) :
			state(state), id(id), parents({ {parent, {} } }), root(root), type(Node_Type::Or),
			dead(false), solved(false), hash(0) {};
		void add_child(Node_Id node);
		void add_parent(Node_Id node, Action action);
		void add_parent(Node_Id node);
		void calculate_hash();
		void set_dead();
		void set_solved();

		const std::vector<Node_Id>&						get_children() const;
		size_t											get_cost() const;
		size_t											get_hash() const;
		Node_Id											get_id() const;
		const Action&									get_parent_action(Node_Id parent) const;
		const std::vector<std::pair<Node_Id, Action>>&	get_parents() const;
		const State&									get_state()const ;
		Node_Type										get_type() const;

		bool is_root_node() const;
		bool is_dead() const;
		bool is_solved() const;
		bool check_if_dead(Graph& graph);
		bool check_if_solved(Graph& graph);
		bool valuate(const Formula& formula, const Domain& domain) const;
		
		std::string to_string(const Domain& domain) const;
		std::string to_graph(const std::string node_id, const std::string state_id, const Domain& domain) const;
		std::string type_to_string() const;

	private:

		bool check_if_dead_and(Graph& graph);
		bool check_if_dead_or(Graph& graph);
		bool check_if_solved_and(Graph& graph);
		bool check_if_solved_or(Graph& graph);

		Node_Type type;
		State state;
		Node_Id id;
		std::vector<std::pair<Node_Id, Action>> parents;
		bool root;
		bool dead;
		bool solved;
		std::vector<Node_Id> children;
		size_t hash;
	};
}