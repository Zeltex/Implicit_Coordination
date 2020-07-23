#include "Action.hpp"
#include "World.hpp"
#include "Domain.hpp"

namespace del {

	// TODO - Check if this constructor is used/should be used anymore. Seems the constructor based on General_Action should be default
	Action::Action(Agent_Id owner, size_t number_of_agents) : cost((size_t)-1), owner(owner), name("Unknown") {
		for (size_t i = 0; i < number_of_agents; i++) {
			edge_conditions.emplace_back(number_of_agents);
		}
	}

	// TODO - Way too many input parameters, just needed it to work
	Action::Action(	General_Action general_action, 
					Agent_Id owner, 
					const std::unordered_map<size_t, Atom_Id>& input_to_atom,
					const std::unordered_map<size_t, std::vector<Agent>>& condition_owner_to_agent)
			: args(input_to_atom), cost(general_action.get_cost()), owner(owner), name(general_action.get_name()), events(),designated_events(){

		//for (auto& entry : condition_owner_to_agent) {
		//	for (auto& agent : entry.second) {
		//		edge_conditions
		//	}
		//}


		std::unordered_map<std::string, Event_Id> event_name_to_id = copy_and_instantiate_events(general_action, input_to_atom);
		copy_and_instantiate_designated_events(general_action, event_name_to_id);
		copy_and_instantiate_edge_conditions(general_action, condition_owner_to_agent, event_name_to_id, input_to_atom);
	}

	void Action::copy_and_instantiate_edge_conditions(
				const General_Action& general_action, 
				const std::unordered_map<size_t, std::vector<Agent>>& condition_owner_to_agent,
				const std::unordered_map<std::string, Event_Id>& event_name_to_id,
				std::unordered_map<size_t, Atom_Id> input_to_atom) {
			
		size_t agents_size = 0;
		edge_conditions = std::vector<Agent_Edges>();
		edge_conditions.reserve(agents_size);
		for (auto& entry : condition_owner_to_agent) {
		
			agents_size += entry.second.size();
		}
		for (auto& entry : condition_owner_to_agent) {
			for (auto& entry2 : entry.second) {
				edge_conditions.emplace_back(agents_size);
			}
		}
		// TODO - Assumes all agents are present in edge definition (meaning _rest pretty much has to be defined)

		for (auto& agent_edges : general_action.get_edge_conditions()) {
			for (auto& agent : condition_owner_to_agent.at(agent_edges.first)) { // Needed for edge conditions for _rest/(REST_KEYWORD)

				if (agent_edges.first == REST_INDEX) {
					input_to_atom[REST_INDEX] = agent.get_atom_id();
				}
				for (auto& edge_condition : agent_edges.second) {
					Formula condition = Formula(edge_condition.condition, input_to_atom);

					edge_conditions.at(agent.get_id().id).insert(event_name_to_id.at(edge_condition.event_from), event_name_to_id.at(edge_condition.event_to), std::move(condition));
				}
			}
		}
	}

	void Action::copy_and_instantiate_designated_events(const General_Action& general_action, const std::unordered_map<std::string, Event_Id>& event_name_to_id) {
		for (auto& entry : general_action.get_designated_events()) {
			this->designated_events.push_back(event_name_to_id.at(entry));
		}
	}

	std::unordered_map<std::string, Event_Id> Action::copy_and_instantiate_events(const General_Action& general_action, const std::unordered_map<size_t, Atom_Id>& input_to_atom) {
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
		return std::move(event_name_to_id);
	}

	void Action::add_event(const Action_Event& event) {
		events.push_back(event);
	}

	void Action::add_event(std::string name, Event_Id id, Formula&& precondition, std::vector<Proposition_Instance>&& proposition_add, std::vector<Proposition_Instance>&& proposition_delete) {
		events.emplace_back(name, id, std::move(precondition), proposition_add, proposition_delete);
	}

	void Action::add_reachability(Agent_Id owner, Event_Id event_from, Event_Id event_to, Formula&& condition) {
		edge_conditions.at(owner.id).insert(event_from, event_to, std::move(condition));
	}

	const std::vector<Action_Event>& Action::get_events() const {
		return events;
	}

	Agent_Id Action::get_owner() const {
		return owner;
	}

	std::string Action::get_name() const {
		return name;
	}

	bool Action::is_event_designated(Event_Id event) const {
		return find(designated_events.begin(), designated_events.end(), event) != designated_events.end();
	}

	bool Action::is_condition_fulfilled(Agent_Id agent, Event_Id event_from, Event_Id event_to, const State& state, const World_Id world) const {
		auto condition = edge_conditions.at(agent.id).get_condition(event_from, event_to);
		if (condition.has_value()) {
			return (*condition.value()).valuate(world.id, &state);
		} else {
			return false;
		}
	}

	void Action::add_designated_event(Event_Id event) {
		designated_events.emplace_back(event);
	}

	std::string Action::to_string(const Domain& domain) const {
		return to_string(0, domain);
	}

	std::string Action::to_string(size_t indenation, const Domain& domain) const {
		size_t relations_size = 0;
		for (auto& agent_relations : edge_conditions) {
			relations_size += agent_relations.size();
		}
		std::string result = get_indentation(indenation) + " Action\n(name, " + name + ") (owner, " + std::to_string(owner.id) + ") (Relations size, " + std::to_string(relations_size) + ") (Designated events";
		for (auto event_id : designated_events) {
			result += ", " + std::to_string(event_id.id);
		}
		result += ")";
		for (auto event : events) {
			result += "\n" + event.to_string(domain);
		}
		return result;
	}

	std::string Action::to_compact_string(const Domain& domain) const {
		std::string result = std::to_string(owner.id);
		for (auto& event : events) {
			result += "\n<" + event.get_preconditions().to_string(domain.get_id_to_atom()) + ",X,X>";
		}
		return result;
	}

	std::string Action::to_graph(const std::string& base_id, const Domain& domain) const {
		std::string result;
		for (auto& event : events) {
			result += base_id + std::to_string(event.get_id().id) + "[label=\"" + event.get_name() + "\n<"
				+ event.get_preconditions().to_string(domain.get_id_to_atom()) + ">\n<"
				+ get_string(event.get_add_list(), domain) + ">\n<"
				+ get_string(event.get_delete_list(), domain) + ">\"";
			if (find(designated_events.begin(), designated_events.end(), event.get_id()) != designated_events.end()) {
				result += ", shape=doublecircle";
			}
			result += "];\n";
		}

		size_t agent = 0;
		for (const auto& agent_relations : edge_conditions) {
			result += agent_relations.to_graph(domain.get_agent(Agent_Id{ agent }).get_name(), base_id, domain);
			agent++;
		}
		return result;
	}

	std::string Action::get_string(const std::vector<Proposition_Instance>& propositions, const Domain& domain) const {
		std::string result;
		bool first = true;
		for (auto& proposition : propositions) {
			if (first) {
				first = false;
			} else {
				result += "; ";
			}
			result += proposition.to_string(domain.get_id_to_atom());
		}
		return result;
	}

	void Action::set_cost(size_t cost) {
		this->cost = cost;
	}

	size_t Action::get_cost() const {
		return cost;
	}
}