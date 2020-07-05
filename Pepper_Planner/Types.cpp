#include "Types.hpp"
#include "Domain.hpp"

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
	std::string Agent_Edges::to_graph(const std::string& agent_name, const std::string& base_id, const Domain& domain) const {
		std::string result;
		// Magic number, estimating around 20 characters per edge
		result.reserve(current_size * 20);
		for (const auto& entry1 : conditions) {
			for (const auto& entry2 : entry1.second) {
				result += base_id + std::to_string(entry1.first) + " -> " + base_id + std::to_string(entry2.first) + "[label=\"" + (agent_name)+":" + entry2.second.to_string(domain.get_id_to_atom()) + "\"];\n";
			}
		}
		return std::move(result);
	}
}