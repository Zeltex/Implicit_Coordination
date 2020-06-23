#pragma once

#include <vector>

#include "State.hpp"
#include "Types.hpp"
#include "../Formula/Formula.hpp"
#include "Action.hpp"

namespace del {
	class Graph;
	class Node {

	public:
		Node() = delete;
		Node(State state, Node_Id id, Node_Id parent, Action action_from_parent, bool root) :
			state(state), id(id), parent(parent), action_from_parent(action_from_parent), root(root), type(Node_Type::And),
			dead(false), solved(false) {};
		// TODO - Don't create dummy action (though it won't get used)
		Node(State state, Node_Id id, Node_Id parent, bool root) :
			state(state), id(id), parent(parent), action_from_parent(Action(Agent_Id{ 0 }, 0)), root(root), type(Node_Type::Or),
			dead(false), solved(false) {};
		void add_child(Node_Id node);
		void set_dead();
		void set_solved();

		const State& get_state()const ;
		Action get_action();
		Node_Id get_id();
		Node_Id get_parent();
		Node_Type get_type() const;
		const Action& get_parent_action() const;
		const std::vector<Node_Id>& get_children() const;

		bool is_root_node() const;
		bool is_dead() const;
		bool is_solved() const;
		bool check_if_dead(Graph& graph);
		bool check_if_solved(Graph& graph);
		bool valuate(const Formula& formula) const;

		std::string to_string() const;
		std::string to_graph(const std::vector<Agent>& agents, const std::string node_id, const std::string state_id) const;
		std::string type_to_string() const;

	private:

		bool check_if_dead_and(Graph& graph);
		bool check_if_dead_or(Graph& graph);
		bool check_if_solved_and(Graph& graph);
		bool check_if_solved_or(Graph& graph);

		Node_Type type;
		State state;
		Node_Id id;
		Node_Id parent;
		Action action_from_parent;
		bool root;
		bool dead;
		bool solved;
		std::vector<Node_Id> children;
	};
}