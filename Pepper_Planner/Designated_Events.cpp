#include "Designated_Events.hpp"
#include "General_Action.hpp"
#include "Action_Events.hpp"

#include <algorithm>

namespace del
{
	Designated_Events::Designated_Events()
	{

	}

	Designated_Events::Designated_Events(const General_Action& general_action, const Action_Events& action_events)
	{
		std::map<std::string, Event_Id> event_name_to_id = action_events.get_name_to_id();
		
		for (const auto& entry : general_action.get_designated_events()) {
			events.push_back(event_name_to_id.at(entry));
		}
	}

	bool Designated_Events::contains(const Event_Id& event_id) const
	{
		return std::find(events.begin(), events.end(), event_id) != events.end();;
	}

	std::string Designated_Events::to_string() const
	{
		std::string result;
		for (const Event_Id& event_id : events) {
			result += ", " + std::to_string(event_id.id);
		}
		return result;
	}
}