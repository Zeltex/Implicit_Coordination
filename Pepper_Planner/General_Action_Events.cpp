#include "General_Action_Events.hpp"
#include "Formula_Buffer.hpp"
#include "Proposition_Instance_Buffer.hpp"

namespace del
{

	General_Action_Event::General_Action_Event(const std::string& name, Event_Id id)
		: name(name), id(id)
	{

	}

	//General_Action_Event::General_Action_Event(const std::string& name, Event_Id id, Formula&& precondition, const Propositions& proposition_add, const Propositions& proposition_delete) :
	//	name(name), id(id), precondition(std::move(precondition)), proposition_add(proposition_add), proposition_delete(proposition_delete) 
	//{
	//
	//}

	void General_Action_Event::set_precondition(Formula formula)
	{
		precondition = std::move(formula);
	}

	void General_Action_Event::set_delete_list(const std::vector<Proposition_Instance>& proposition_instances)
	{
		proposition_add = proposition_instances;
	}
	
	void General_Action_Event::set_add_list(const std::vector<Proposition_Instance>& proposition_instances)
	{
		proposition_delete = proposition_instances;
	}

	void General_Action_Events::start(const std::string& name)
	{
		events.push_back({ name, Event_Id{events.size()} });
	}

	void General_Action_Events::set_preconditions(Formula_Buffer& formula_buffer)
	{
		events.back().set_precondition(formula_buffer.get());
	}

	size_t General_Action_Events::size() const
	{
		return events.size();
	}

	void General_Action_Events::set_delete_list(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		events.back().set_delete_list(proposition_instance_buffer.get());
	}

	void General_Action_Events::set_add_list(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		events.back().set_add_list(proposition_instance_buffer.get());
	}
}