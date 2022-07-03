#pragma once

#include "Types.hpp"

#include <vector>

namespace del
{
	class General_Action;
	class Action_Events;
	class Designated_Events
	{
	public:
		Designated_Events();
		Designated_Events(const General_Action& general_action, const Action_Events& action_events);
		bool contains(const Event_Id& event_id) const;
		std::string to_string() const;
	private:
		std::vector<Event_Id> events;
	};
}