#include "Graph.hpp"

#include "Agents.hpp"
#include "Core.hpp"
#include "Node_Comparator.hpp"
#include "State.hpp"

#include <assert.h>

namespace del {

	Graph::~Graph()
	{
		for (Node* node : nodes)
		{
			delete node;
		}
	}

	Graph::Graph()
		: root(), frontier(), nodes(std::vector<Node*>()) 
	{
	
	};

	Graph::Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent& planning_agent) 
	{
		nodes.reserve(node_size); 
		Node* root = create_root_node(state);
		history.insert(root);

		for (State& global : state.split_into_globals()) 
		{
			Node* node = create_or_node(global, root);
			history.insert(node);
			add_to_frontier(node);
		}
	}

	Node* Graph::get_next_from_frontier() 
	{
		Node* node = frontier.top();
		frontier.pop();
		return node;
	}

	bool Graph::is_frontier_empty() const 
	{
		return frontier.empty();
	}

	Node* Graph::create_or_node(State state, Node* parent) 
	{
		Node* node = new Node(state, Node_Id{ nodes.size() }, parent, false);
		nodes.push_back(node);
		node->calculate_hash();
		parent->add_child(node);
		return node;
	}

	Node* Graph::create_and_node(State state, Node* parent, const Action* action_from_parent)
	{
		Node* node = new Node(state, Node_Id{ nodes.size() }, parent, action_from_parent, false);
		nodes.push_back(node);
		node->calculate_hash();
		parent->add_child(node);
		return node;
	}

	Node* Graph::create_root_node(State state) 
	{
		// The dummy action makes sure root is and-node
		Node* node = new Node(state, Node_Id{ nodes.size() }, nullptr, nullptr, true);
		nodes.push_back(node);
		node->calculate_hash();
		root = node;
		return node;
	}

	void Graph::add_to_frontier(Node* node)
	{
		frontier.push(node);
	}

	void Graph::set_parent_child(Node* parent, Node* child, const Action* action)
	{
		child->add_parent(parent, action);
		parent->add_child(child);
	}

	void Graph::set_parent_child(Node* parent, Node* child) 
	{
		child->add_parent(parent);
		parent->add_child(child);
	}

	const std::vector<Node*>& Graph::get_const_nodes() const 
	{
		return nodes;
	}

	std::vector<Node*>& Graph::get_nodes() 
	{
		return nodes;
	}

	Node* Graph::get_root_node() 
	{
		return root;
	}

	std::string Graph::to_string(const Domain& domain) const 
	{
		std::string result = "Graph: (root, " + std::to_string(root->get_id().id) + ") (frontier";
		result += ")";
		for (auto node : nodes) {
			result += "\n\n\n" + node->to_string(domain);
		}
		return result;
	}

}
