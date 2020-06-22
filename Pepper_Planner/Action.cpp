#include "Action.hpp"

namespace del {

	Action::Action(Agent_Id owner, size_t number_of_agents) : owner(owner) {
		for (size_t i = 0; i < number_of_agents; i++) {
			indistinguishability_relation.emplace_back();
		}
	}
	Action::Action(General_Action general_action, Agent_Id owner, const std::unordered_map<std::string, std::string>& input_to_atom): 
		owner(owner), events(),designated_events(), indistinguishability_relation() {
		this->owner = owner;
		std::unordered_map<std::string, Event_Id> event_name_to_id;

		for (auto& event : general_action.get_events()) {
			std::vector<Proposition_Instance> add_list;
			std::vector<Proposition_Instance> delete_list;
			for (auto& entry : event.get_add_list()) {
				add_list.emplace_back(entry, input_to_atom);
			}
			for (auto& entry : event.get_delete_list()) {
				delete_list.emplace_back(entry, input_to_atom);
			}
			Formula preconditions = Formula(event.get_preconditions(), input_to_atom);
			auto id = Event_Id{ events.size() };
			event_name_to_id.emplace(event.get_name(), Event_Id{ id.id });

			add_event(event.get_name(), id, std::move(preconditions), std::move(add_list), std::move(delete_list));
		}		

		size_t agent_counter = 0;
		for (auto& agent_relations : general_action.get_reachability_relations()) {
			indistinguishability_relation.emplace_back();
			for (auto& relation : agent_relations) {
				indistinguishability_relation[agent_counter].push_back(relation);
			}
			agent_counter++;
		}

		for (auto& entry : general_action.get_designated_events()) {
			this->designated_events.push_back(event_name_to_id.at(entry));
		}
	}

	void Action::add_event(const Action_Event& event) {
		events.push_back(event);
	}

	void Action::add_event(std::string name, Event_Id id, Formula&& precondition, std::vector<Proposition_Instance>&& proposition_add, std::vector<Proposition_Instance>&& proposition_delete) {
		events.emplace_back(name, id, std::move(precondition), proposition_add, proposition_delete);
	}

	const std::vector<Action_Event>& Action::get_events() const {
		return events;
	}

	Agent_Id Action::get_owner() const {
		return owner;
	}

	bool Action::is_one_reachable(Agent_Id agent, Event_Id event1, Event_Id event2) const {
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
		return to_string(0);
	}

	std::string Action::to_string(size_t indenation) const {
		size_t relations_size = 0;
		for (auto agent_relations : indistinguishability_relation) {
			for (auto relation : agent_relations) {
				relations_size++;
			}
		}
		std::string result = get_indentation(indenation) + " Action\n(owner, " + std::to_string(owner.id) + ") (Relations size, " + std::to_string(relations_size) + ") (Designated events";
		for (auto event_id : designated_events) {
			result += ", " + std::to_string(event_id.id);
		}
		result += ")";
		for (auto event : events) {
			result += "\n" + event.to_string();
		}
		return result;
	}

	std::string Action::to_compact_string() const {
		std::string result;
		for (auto& event : events) {
			result += "<" + event.get_preconditions().to_string() + ",X,X>";
		}
		return result;
	}
}