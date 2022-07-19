#include "General_Actions.hpp"

#include "Action.hpp"
#include "Atoms.hpp"
#include "Domain.hpp"
#include "Edge_Conditions.hpp"
#include "Formula_Core.hpp"
#include "General_Domain.hpp"
#include "Propositions_Lookup.hpp"
#include "Variables_Buffer.hpp"

#include <assert.h>

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

	size_t General_Action::get_cost() const {
		return cost;
	}

	std::pair<std::string, Atom_Id> General_Action::get_owner() const{
		return owner;
	}

	std::string General_Action::get_name() const {
		return name;
	}

	const General_Action_Events& General_Action::get_events() const {
		return events;
	}

	const General_Agent_Edge_Conditions& General_Action::get_edge_conditions() const {
		return edge_conditions;
	}

	void General_Action::set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions)
	{
		this->edge_conditions.insert(agent_name, edge_conditions);
	}

	void General_Action::set_events(General_Action_Events& general_action_events)
	{
		events = general_action_events.get();
	}

	void General_Action::set_propositions_buffer(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		this->proposition_instance_buffer.set_and_consume(proposition_instance_buffer);
	}

	void General_Actions::start(const std::string name)
	{
		actions.push_back(std::make_unique<General_Action>(name));
	}

	void General_Actions::set_input(Inputs_Buffer& inputs_buffer)
	{
		actions.back()->inputs = inputs_buffer.get();
	}

	void General_Actions::set_owner(const std::string type, const std::string name)
	{
		actions.back()->owner = { type, actions.back()->inputs.get_index({type, name}) };
	}

	void General_Actions::set_cost(size_t cost)
	{
		actions.back()->cost = cost;
	}

	void General_Actions::set_edge_conditions(const std::string agent_name, General_Edge_Conditions& edge_conditions)
	{
		actions.back()->set_edge_conditions(agent_name, edge_conditions);
	}

	void General_Actions::set_events(General_Action_Events& general_action_events)
	{
		actions.back()->set_events(general_action_events);
	}

	void General_Actions::set_propositions_buffer(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		actions.back()->set_propositions_buffer(proposition_instance_buffer);
	}

	std::vector<std::unique_ptr<General_Action>> General_Actions::get()
	{
		auto temp = std::move(actions);
		actions.clear();
		return std::move(temp);

	}

	const Inputs& General_Actions::get_inputs() const
	{
		return actions.back()->get_inputs();
	}
}
