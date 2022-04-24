#include "General_Action.hpp"
#include "Action.hpp"
#include "Domain.hpp"
#include "Formula_Core.hpp"
#include "Edge_Conditions.hpp"

namespace del {

	void General_Action::set_cost(size_t cost) {
		this->cost = cost;
	}

	void General_Action::set_owner(std::string type, Atom_Id name) {
		owner = { type, name };
	}

	void General_Action::set_name(std::string name) {
		this->name = name;
	}

	void General_Action::set_designated_events(std::vector<std::string> designated_events) {
		this->designated_events = designated_events;
	}

	void General_Action::set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) {
		this->inputs = inputs;
	}

	void General_Action::create_event(std::string name, Formula&& preconditions, const std::vector<Proposition>& add_list, const std::vector<Proposition>& delete_list) {
		events.insert(name, std::move(preconditions), add_list, delete_list);
	}

	void General_Action::add_edge_condition(Atom_Id agent, General_Edge_Conditions&& edge_conditions_input) {
		edge_conditions.insert(agent.id, std::move(edge_conditions_input) );
	} 

	size_t General_Action::get_cost() const {
		return cost;
	}


	const std::vector<std::pair<std::string, std::string>>& General_Action::get_inputs() const {
		return inputs;
	}

	std::pair<std::string, Atom_Id> General_Action::get_owner() const{
		return owner;
	}

	std::string General_Action::get_name() const {
		return name;
	}

	const std::vector<std::string>& General_Action::get_designated_events() const {
		return designated_events;
	}

	const General_Action_Events& General_Action::get_events() const {
		return events;
	}

	const General_Agent_Edge_Conditions& General_Action::get_edge_conditions() const {
		return edge_conditions;
	}

	
	void General_Action::set_instance_to_proposition(std::map<Proposition_Instance, Proposition> instance_to_proposition) {
		input_to_formula = instance_to_proposition;
	}

	std::map<Proposition, Proposition> General_Action::create_converter(const Domain& domain, const std::map<size_t, Atom_Id>& arguments) const {
		std::map<Proposition, Proposition> formula_to_domain;
		for (auto& [prop_instance, prop] : input_to_formula) {
			auto grounded_prop_instance = Proposition_Instance(prop_instance, arguments);
			formula_to_domain[prop] = domain.get_proposition(grounded_prop_instance);
		}
		return formula_to_domain;
	}

	std::map<Proposition, Proposition> General_Action::create_converter(const Domain& domain, const std::vector<Atom_Id>& arguments) const{
		std::map<Proposition, Proposition> formula_to_domain;
		for (auto& [prop_instance, prop] : input_to_formula) {
			if (!prop_instance.contains_non_atom_entry()) {
				auto grounded_prop_instance = Proposition_Instance(prop_instance, arguments);
				formula_to_domain[prop] = domain.get_proposition(grounded_prop_instance);
			}
		}
		return formula_to_domain;
	}


	const std::map<Proposition, Proposition>& General_Action::get_converter() const {
		return formula_to_domain;
	}
}
