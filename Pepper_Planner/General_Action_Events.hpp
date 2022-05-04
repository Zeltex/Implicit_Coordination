#pragma once

#include <vector>
#include <string>

#include "Formula.hpp"
#include "Types.hpp"
#include "Propositions.hpp"

namespace del
{
	class General_Action_Event
	{
	friend class Action_Event;
	public:
		General_Action_Event(std::string name, Event_Id id, Formula&& precondition, const Propositions& proposition_add, const Propositions& proposition_delete);
	private:
		std::string name;
		Event_Id id;
		Formula precondition;
		Propositions proposition_add;
		Propositions proposition_delete;
	};

	class General_Action_Events
	{
	friend class Action_Events;
	public:	
		void insert(std::string name, Formula&& preconditions, const Propositions& add_list, const Propositions& delete_list);
		size_t size() const;
	private:
		std::vector<General_Action_Event> events;
	};
}