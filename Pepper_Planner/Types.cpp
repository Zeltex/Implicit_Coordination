#include "Types.hpp"
#include "Domain.hpp"
#include "Node.hpp"
#include "State.hpp"

namespace del {
	
	void Agent_Edges::insert(Event_Id event_from, Event_Id event_to, Formula&& condition) {
		auto it = conditions.find(event_from.id);
		if (it == conditions.end()) {
			conditions.insert({ event_from.id, {} });
		}
		conditions[event_from.id][event_to.id] = std::move(condition);
		current_size++;
	}
	
	std::optional<const Formula*> Agent_Edges::get_condition(Event_Id event_from, Event_Id event_to) const {
		auto it1 = conditions.find(event_from.id);
		if (it1 != conditions.end()) {
			auto it2 = it1->second.find(event_to.id);
			if (it2 != conditions.at(event_from.id).end()) {
				return { &(it2->second) };
			}
		}
		return {};
	}

	size_t Agent_Edges::size() const {
		return this->current_size;
	}

	bool Node_Entry_Comparator::operator()(const Node_Entry& lhs, const Node_Entry& rhs) {
		return lhs.cost > rhs.cost;
	}

	std::size_t State_Hasher::operator()(const State& state) const
	{
		return state.to_hash();
	}
}