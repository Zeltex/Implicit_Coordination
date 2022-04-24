#pragma once

#include <vector>
#include <string>

#include "Formula.hpp"
#include "Types.hpp"

namespace del
{
	class General_Action_Event
	{
	friend class Action_Event;
	public:
		General_Action_Event(std::string name, Event_Id id, Formula&& precondition, const std::vector<Proposition>& proposition_add, const std::vector<Proposition>& proposition_delete);
	private:
		std::string name;
		Event_Id id;
		Formula precondition;
		std::vector<Proposition> proposition_add;
		std::vector<Proposition> proposition_delete;
	};

	class General_Action_Events
	{
	friend class Action_Events;
	public:	
		void insert(std::string name, Formula&& preconditions, const std::vector<Proposition>& add_list, const std::vector<Proposition>& delete_list);
		size_t size() const;
	private:
		std::vector<General_Action_Event> events;
	};
}