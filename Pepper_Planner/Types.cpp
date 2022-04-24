#include "Types.hpp"
#include "Domain.hpp"
#include "Node.hpp"
#include "State.hpp"

namespace del {
	bool Node_Entry_Comparator::operator()(const Node_Entry& lhs, const Node_Entry& rhs) {
		return lhs.cost > rhs.cost;
	}

	std::size_t State_Hasher::operator()(const State& state) const
	{
		return state.to_hash();
	}
}