#include "General_Action_Events.hpp"

namespace del
{
	General_Action_Event::General_Action_Event(std::string name, Event_Id id, Formula&& precondition, const Propositions& proposition_add, const Propositions& proposition_delete) :
		name(name), id(id), precondition(std::move(precondition)), proposition_add(proposition_add), proposition_delete(proposition_delete) 
	{
	
	}

	void General_Action_Events::insert(std::string name, Formula && preconditions, const Propositions& add_list, const Propositions& delete_list)
	{
		events.emplace_back(name, Event_Id{ events.size() }, std::move(preconditions), add_list, delete_list);
	}

	size_t General_Action_Events::size() const
	{
		return events.size();
	}
}