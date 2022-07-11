#include "NodeBase.hpp"

#include <assert.h>

namespace del
{

	void NodeBase::set_dead()
	{
		dead = true;
	}

	void NodeBase::set_solved()
	{
		solved = true;
	}

	size_t NodeBase::get_hash() const
	{
		assert(hash != EMPTY_INDEX);
		return hash;
	}

	Node_Id	NodeBase::get_id() const
	{
		return id;
	}

	int NodeBase::get_value() const
	{
		return value;
	}

	bool NodeBase::has_value() const
	{
		return value != EMPTY_VALUE && value != UNKNOWN_VALUE;
	}

	bool NodeBase::is_root_node() const
	{
		return root;
	}
	
	bool NodeBase::is_dead() const
	{
		return dead;
	}
	
	bool NodeBase::is_solved() const
	{
		return solved;
	}
}