#include "Action.hpp"
#include "World.hpp"
#include "Domain.hpp"
#include "Formula_Input_Impl.hpp"

namespace del {

	// TODO - Check if this constructor is used/should be used anymore. Seems the constructor based on General_Action should be default
	Action::Action(Agent_Id owner, size_t number_of_agents) : cost((size_t)-1), owner(owner), name("Unknown") {
		for (size_t i = 0; i < number_of_agents; i++) {
			edge_conditions.emplace_back(number_of_agents);
		}
	}

	Action::Action(const General_Action& general_action, const Domain& domain, const std::vector<Atom_Id>& arguments)
			:args(arguments), cost(general_action.get_cost()), name(general_action.get_name()), events(), designated_events() {

		auto& owner_atom = arguments.at(general_action.get_owner().second.id);
		this->owner = domain.get_agent_from_atom(owner_atom).get_id();

		auto condition_owner_to_agent = general_action.get_condition_owner_to_agent(domain, arguments);
		auto event_name_to_id = copy_and_instantiate_events(general_action, arguments, domain);
		copy_and_instantiate_designated_events(general_action, event_name_to_id);
		//copy_and_instantiate_edge_conditions(general_action, condition_owner_to_agent, event_name_to_id, input_to_atom, input_to_agent);
	}



	//void Action::copy_and_instantiate_edge_conditions(
	//			const General_Action& general_action, 
	//			const std::unordered_map<size_t, std::vector<Agent>>& condition_owner_to_agent,
	//			const std::unordered_map<std::string, Event_Id>& event_name_to_id,
	//			const std::vector<Atom_Id>& arguments) {
	//		
	//	size_t agents_size = 0;
	//	edge_conditions = std::vector<Agent_Edges>();
	//	edge_conditions.reserve(agents_size);
	//	for (auto& entry : condition_owner_to_agent) {
	//		agents_size += entry.second.size();
	//	}
	//	for (auto& entry : condition_owner_to_agent) {
	//		for (auto& entry2 : entry.second) {
	//			edge_conditions.emplace_back(agents_size);
	//		}
	//	}
	//	// TODO - Assumes all agents are present in edge definition (meaning _rest pretty much has to be defined)

	//	for (auto& agent_edges : general_action.get_edge_conditions()) {
	//		for (auto& agent : condition_owner_to_agent.at(agent_edges.first)) { // Needed for edge conditions for _rest/(REST_KEYWORD)

	//			if (agent_edges.first == REST_INDEX) {
	//				input_to_atom[REST_INDEX] = agent.get_atom_id();
	//			}
	//			for (auto& edge_condition : agent_edges.second) {
	//				Formula condition = Formula(edge_condition.condition, input_to_atom, input_to_agent);

	//				edge_conditions.at(agent.get_id().id).insert(event_name_to_id.at(edge_condition.event_from), event_name_to_id.at(edge_condition.event_to), std::move(condition));
	//			}
	//		}
	//	}
	//}

	void Action::copy_and_instantiate_designated_events(const General_Action& general_action, const std::unordered_map<std::string, Event_Id>& event_name_to_id) {
		for (auto& entry : general_action.get_designated_events()) {
			this->designated_events.push_back(event_name_to_id.at(entry));
		}
	}

	std::unordered_map<std::string, Event_Id> Action::copy_and_instantiate_events(const General_Action& general_action, const std::vector<Atom_Id>& arguments, const Domain& domain) {
		std::unordered_map<std::string, Event_Id> event_name_to_id;
		auto converter = general_action.create_converter(domain, arguments);
		for (auto& event : general_action.get_events()) {
			std::vector<Proposition> add_list;
			std::vector<Proposition> delete_list;
			for (auto& entry : event.get_add_list()) {
				add_list.push_back(converter.at(entry));
			}
			for (auto& entry : event.get_delete_list()) {
				delete_list.push_back(converter.at(entry));
			}
			Formula preconditions = Formula(event.get_preconditions(), converter);
			auto id = Event_Id{ events.size() };
			event_name_to_id.emplace(event.get_name(), id);

			add_event(event.get_name(), id, std::move(preconditions), std::move(add_list), std::move(delete_list));
		}
		return std::move(event_name_to_id);
	}

	void Action::add_event(const Action_Event& event) {
		events.push_back(event);
	}

	void Action::add_event(const std::string& name, Event_Id id, Formula&& precondition, std::vector<Proposition>&& proposition_add, std::vector<Proposition>&& proposition_delete) {
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

	bool Action::is_condition_fulfilled(Agent_Id agent, Event_Id event_from, Event_Id event_to, const State& state, const World_Id world, const Domain& domain) const {
		auto condition = edge_conditions.at(agent.id).get_condition(event_from, event_to);
		if (condition.has_value()) {
			Formula_Input_Impl input = { &state, &domain };
			return (*condition.value()).valuate(world.id, &input);
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

	std::string Action::get_string(const std::vector<Proposition>& propositions, const Domain& domain) const {
		std::string result;
		bool first = true;
		for (auto& proposition : propositions) {
			if (first) {
				first = false;
			} else {
				result += "; ";
			}
			result += domain.get_proposition_instance(proposition).to_string(domain.get_id_to_atom());
		}
		return result;
	}

	void Action::set_cost(size_t cost) {
		this->cost = cost;
	}

	void Action::set_name(const std::string& name) {
		this->name = name;
	}

	size_t Action::get_cost() const {
		return cost;
	}
}