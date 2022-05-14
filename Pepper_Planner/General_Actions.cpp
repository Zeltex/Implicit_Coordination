#include "General_Actions.hpp"
#include "Action.hpp"
#include "Domain.hpp"
#include "Formula_Core.hpp"
#include "Edge_Conditions.hpp"
#include "Atoms.hpp"
#include "General_Domain.hpp"
#include "Variables_Buffer.hpp"

namespace del {


	General_Action::General_Action(const std::string& name)
		: General_Action()
	{
		this->name = name;
	}

	void General_Action::set_cost(size_t cost) {
		this->cost = cost;
	}

	void General_Action::set_owner(std::string type, Atom_Id name) {
		owner = { type, name };
	}

	const Inputs& General_Action::get_inputs() const
	{
		return inputs;
	}

	void General_Action::set_name(std::string name) {
		this->name = name;
	}

	void General_Action::set_designated_events(std::vector<std::string> designated_events) {
		this->designated_events = designated_events;
	}

	//void General_Action::set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) {
	//	this->inputs = inputs;
	//}

	//void General_Action::create_event(std::string name, Formula&& preconditions, const std::vector<Proposition>& add_list, const std::vector<Proposition>& delete_list) {
	//	events.insert(name, std::move(preconditions), add_list, delete_list);
	//}

	size_t General_Action::get_cost() const {
		return cost;
	}


	//const std::vector<std::pair<std::string, std::string>>& General_Action::get_inputs() const {
	//	return inputs;
	//}

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

	std::map<Proposition, Proposition> General_Action::create_converter(const Domain& domain, const Atoms& arguments) const{
		std::map<Proposition, Proposition> formula_to_domain;
		for (auto& [prop_instance, prop] : input_to_formula) {
			if (!prop_instance.contains_non_atom_entry()) {
				auto grounded_prop_instance = Proposition_Instance(prop_instance, arguments);
				formula_to_domain[prop] = domain.get_proposition(grounded_prop_instance);
			}
		}
		return formula_to_domain;
	}

	//const std::map<Proposition, Proposition>& General_Action::get_converter() const {
	//	return formula_to_domain;
	//}

	void General_Action::set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions)
	{
		Atom_Id atom_id{ inputs.get_index(agent_name) };
		this->edge_conditions.insert(atom_id, edge_conditions);
	}

	void General_Actions::start(const std::string name)
	{
		actions.push_back(General_Action{ name });
	}

	void General_Actions::set_input(Inputs_Buffer& inputs_buffer)
	{
		actions.back().inputs = inputs_buffer.get();
	}

	void General_Actions::set_owner(const std::string type, const std::string name)
	{
		General_Action action = actions.back();
		size_t index = action.inputs.get_index({ type, name });
		action.owner = { type, index };
	}

	void General_Actions::set_designated_events(Variables_Buffer& variables_buffer)
	{
		actions.back().designated_events = variables_buffer.get();
	}

	void General_Actions::set_cost(size_t cost)
	{
		actions.back().cost = cost;
	}

	void General_Actions::set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions)
	{
		actions.back().set_edge_conditions(agent_name, edge_conditions);
	}

	const Inputs& General_Actions::get_inputs() const
	{
		return actions.back().get_inputs();
	}
}
