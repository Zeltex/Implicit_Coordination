#include "Action.hpp"

namespace del {

	Action::Action(Agent_Id owner, size_t number_of_agents) : owner(owner) {
		for (size_t i = 0; i < number_of_agents; i++) {
			indistinguishability_relation.emplace_back();
		}
	}

	void Action::add_event(const Action_Event& event) {
		events.push_back(event);
		//events.emplace_back(event);
	}

	void Action::add_event(Event_Id id, Formula&& precondition, std::unordered_set<std::string>&& proposition_add, std::unordered_set<std::string>&& proposition_delete) {
		events.emplace_back(id, std::move(precondition), proposition_add, proposition_delete);
	}

	std::vector<Action_Event>& Action::get_events() {
		return events;
	}

	Agent_Id Action::get_owner() {
		return owner;
	}

	bool Action::is_one_reachable(Agent_Id agent, Event_Id event1, Event_Id event2) {
		for (auto relations : indistinguishability_relation[agent.id]) {
			if (relations.event_from == event1 && relations.event_to == event2) {
				return true;
			}
		}
		return false;
	}


	bool Action::is_event_designated(Event_Id event) const {
		return find(designated_events.begin(), designated_events.end(), event) != designated_events.end();
	}

	void Action::add_indistinguishability_relation(Agent_Id agent, Event_Id event_from, Event_Id event_to) {
		indistinguishability_relation[agent.id].emplace_back(event_from, event_to);
	}

	void Action::add_designated_event(Event_Id event) {
		designated_events.emplace_back(event);
	}

	std::string Action::to_string() const {
		size_t relations_size = 0;
		for (auto agent_relations : indistinguishability_relation) {
			for (auto relation : agent_relations) {
				relations_size++;
			}
		}
		std::string result = "(owner, " + std::to_string(owner.id) + ") (Relations size, " + std::to_string(relations_size) + ") (Designated events";
		for (auto event_id : designated_events) {
			result += ", " + std::to_string(event_id.id);
		}
		result += ")";
		for (auto event : events) {
			result += "\n" + event.to_string();
		}
		return result;
	}
}