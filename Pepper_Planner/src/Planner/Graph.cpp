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
		: root(), frontier(), nodes() 
	{
	
	};

	Graph::Graph(size_t node_size, const State& state, Node_Comparator& history, const Agent* planning_agent) 
	{
		nodes.reserve(node_size); 
		NodeAnd* root = create_root_node(state);
		history.insert(root);

		for (State& global : state.split_into_globals()) 
		{
			NodeOr* node = create_or_node(std::move(global), root);
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

	NodeOr* Graph::create_or_node(State state, NodeAnd* parent)
	{
		NodeOr* node = new NodeOr(std::move(state), Node_Id{ nodes.size() }, parent);
		node->calculate_hash();
		nodes.push_back(node);
		parent->add_child(node);
		return node;
	}

	NodeAnd* Graph::create_and_node(State state, NodeOr* parent, const Action* action_from_parent)
	{
		NodeAnd* node = new NodeAnd(std::move(state), Node_Id{ nodes.size() }, parent);
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

	void Graph::calculate_value()
	{
		std::deque<NodeBase*> frontier;
		for (auto& node : nodes)
		{
			if (node->is_leaf())
			{
				frontier.push_back(node);
			}
		}

		while (!frontier.empty())
		{
			auto node = frontier.front();
			frontier.pop_front();
			node->calculate_value(frontier);
			if (node->is_root_node() && node->has_value())
			{
				break;
			}
		}

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
