#include "Graph.hpp"

#include "Agents.hpp"
#include "Core.hpp"
#include "Domain.hpp"
#include "NodeBase.hpp"
#include "NodeAnd.hpp"
#include "NodeOr.hpp"
#include "Node_Comparator.hpp"
#include "State.hpp"

#include <assert.h>

namespace del {

	Graph::~Graph()
	{
		for (NodeBase* node : nodes)
		{
			delete node;
		}
	}

	Graph::Graph()
		: root(), frontier(), nodes(std::vector<NodeBase*>()) 
	{
	
	};

	Graph::Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent& planning_agent) 
	{
		nodes.reserve(node_size); 
		NodeAnd* root = create_root_node(state);
		history.insert(root);

		for (State& global : state.split_into_globals()) 
		{
			NodeOr* node = create_or_node(root, global.get_designated_worlds());
			history.insert(node);
			add_to_frontier(node);
		}
	}

	NodeOr* Graph::get_next_from_frontier() 
	{
		NodeOr* node = frontier.top();
		frontier.pop();
		return node;
	}

	bool Graph::is_frontier_empty() const 
	{
		return frontier.empty();
	}

	NodeOr* Graph::create_or_node(NodeAnd* parent, const std::set<World_Id>& designated_worlds)
	{
		assert(designated_worlds.size() == 1);
		NodeOr* node = new NodeOr(Node_Id{ nodes.size() }, parent, *designated_worlds.begin());
		node->calculate_hash();
		nodes.push_back(node);
		parent->add_child(node);
		return node;
	}

	NodeAnd* Graph::create_and_node(State state, NodeOr* parent, const Action* action_from_parent)
	{
		NodeAnd* node = new NodeAnd(state, Node_Id{ nodes.size() }, parent);
		node->calculate_hash();
		nodes.push_back(node);
		parent->add_child(node, action_from_parent);
		return node;
	}

	NodeAnd* Graph::create_root_node(const State& state)
	{
		NodeAnd* node = new NodeAnd(state, Node_Id{ nodes.size() });
		node->calculate_hash(); 
		nodes.push_back(node);
		root = node;
		return node;
	}

	void Graph::add_to_frontier(NodeOr* node)
	{
		frontier.push(node);
	}

	const std::vector<NodeBase*>& Graph::get_const_nodes() const 
	{
		return nodes;
	}

	std::vector<NodeBase*>& Graph::get_nodes() 
	{
		return nodes;
	}

	NodeAnd* Graph::get_root_node()
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
