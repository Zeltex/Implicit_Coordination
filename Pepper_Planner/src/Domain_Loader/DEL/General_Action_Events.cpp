#include "General_Action_Events.hpp"

#include "Formula_Buffer.hpp"

namespace del
{

	General_Action_Event::General_Action_Event(const std::string& name, Event_Id id)
		: name(name), id(id)
	{

	}

	void General_Action_Event::set_precondition(General_Formula&& formula)
	{
		precondition = std::move(formula);
	}

	void General_Action_Event::set_delete_list(const std::vector<General_Proposition_Instance>& proposition_instances)
	{
		proposition_delete = proposition_instances;
	}
	
	void General_Action_Event::set_add_list(const std::vector<General_Proposition_Instance>& proposition_instances)
	{
		proposition_add = proposition_instances;
	}

	void General_Action_Event::set_instance_buffer(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		this->proposition_instance_buffer = proposition_instance_buffer.move();
	}

	General_Action_Events::General_Action_Events()
		: events()
	{

	}

	General_Action_Events::General_Action_Events(std::vector<std::unique_ptr<General_Action_Event>> events)
		: events(std::move(events))
	{

	}

	std::vector<std::unique_ptr<General_Action_Event>> General_Action_Events::get()
	{
		return std::move(events);
	}

	void General_Action_Events::start(const std::string& name)
	{
		events.emplace_back(new General_Action_Event(name, Event_Id{events.size()}));
	}

	void General_Action_Events::end(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		events.back()->set_instance_buffer(proposition_instance_buffer);
	}

	void General_Action_Events::set_preconditions(Formula_Buffer& formula_buffer)
	{
		events.back()->set_precondition(std::move(formula_buffer.get()));
	}

	size_t General_Action_Events::size() const
	{
		return events.size();
	}

	void General_Action_Events::set_delete_list(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		events.back()->set_delete_list(proposition_instance_buffer.get());
	}

	void General_Action_Events::set_add_list(Proposition_Instance_Buffer& proposition_instance_buffer)
	{
		events.back()->set_add_list(proposition_instance_buffer.get());
	}
}