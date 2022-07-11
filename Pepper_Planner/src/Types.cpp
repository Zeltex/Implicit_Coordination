#include "Types.hpp"

#include "Domain.hpp"
#include "NodeOr.hpp"
#include "NodeBase.hpp"
#include "State.hpp"

namespace del {
	bool Node_Entry_Comparator::operator()(const Node_Entry& lhs, const Node_Entry& rhs) 
	{
		return lhs.cost > rhs.cost;
	}

	bool Node_Cost_Comparator::operator()(const NodeOr* lhs, const NodeOr* rhs)
	{
		return lhs->get_cost() > rhs->get_cost();
	}

	std::size_t State_Hasher::operator()(const State& state) const
	{
		return state.to_hash();
	}
}