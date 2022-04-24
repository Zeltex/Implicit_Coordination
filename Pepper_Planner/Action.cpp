#include "Action.hpp"
#include "World.hpp"
#include "Domain.hpp"
#include "Formula_Input_Impl.hpp"

namespace del {

	Action::Action(const General_Action& general_action, const Domain& domain, const std::vector<Atom_Id>& arguments)
			:args(arguments), cost(general_action.get_cost()), name(general_action.get_name()), events(), designated_events() 
	{

		const Atom_Id& owner_atom = arguments.at(general_action.get_owner().second.id);
		this->owner = domain.get_agent_from_atom(owner_atom).get_id();



		auto event_name_to_id = copy_and_instantiate_events(general_action, arguments, domain);
		copy_and_instantiate_designated_events(general_action, event_name_to_id);


		edge_conditions = Agent_Edge_Conditions(general_action, domain, event_name_to_id, arguments);
	}

	void Action::copy_and_instantiate_designated_events(const General_Action& general_action, const std::map<std::string, Event_Id>& event_name_to_id) {
		for (auto& entry : general_action.get_designated_events()) {
			this->designated_events.push_back(event_name_to_id.at(entry));
		}
	}

	std::map<std::string, Event_Id> Action::copy_and_instantiate_events(const General_Action& general_action, const std::vector<Atom_Id>& arguments, const Domain& domain)
	{
		std::map<std::string, Event_Id> event_name_to_id;
		auto converter = general_action.create_converter(domain, arguments);
		for (auto& event : general_action.get_events()) 
		{
			Formula preconditions = Formula(event.get_preconditions(), converter);
			auto id = Event_Id{ events.size() };
			event_name_to_id.emplace(event.get_name(), id);

			add_event(event.get_name(), id, std::move(preconditions), event.get_add_list(), event.get_delete_list());
		}
		return event_name_to_id;
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
		auto condition = edge_conditions.get_precondition(agent, event_from, event_to);
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
		size_t relations_size = edge_conditions.size();
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