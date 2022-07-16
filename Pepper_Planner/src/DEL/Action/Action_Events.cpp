#include "Action_Events.hpp"

#include "Agents.hpp"
#include "Atoms.hpp"
#include "Converter_Base.hpp"
#include "Converter_Action.hpp"
#include "Propositions_Lookup.hpp"

#include <assert.h>

namespace del {

	Action_Event::Action_Event(const std::unique_ptr<General_Action_Event>& other, Event_Id id, const Converter_Base* converter, const Propositions_Lookup& propositions_lookup, const Atoms& arguments)
		: name(other->name), 
		id(id), 
		precondition(other->precondition, converter),
		proposition_add(other->proposition_add, converter),
		proposition_delete(other->proposition_delete, converter)
	{

	}

	Event_Id Action_Event::get_id() const {
		return id;
	}

	const Propositions& Action_Event::get_add_list() const {
		return proposition_add;
	}

	const Propositions& Action_Event::get_delete_list() const {
		return proposition_delete;
	}

	const Formula& Action_Event::get_preconditions() const {
		return precondition;
	}

	std::string Action_Event::get_name() const {
		return name;
	}

	std::string Action_Event::to_string() const {
		return "Event " 
			+ std::to_string(id.id) 
			+ ": (Preconditions: " 
			+ precondition.to_string() 
			+ ") (Add list"
			+ proposition_add.to_string()
			+ ") (Delete list, "
			+ proposition_delete.to_string()
			+ ")";
	}

	Action_Events::Action_Events()
	{

	}

	Action_Events::Action_Events(const General_Action& general_action, const Atoms& arguments, const Propositions_Lookup& propositions_lookup, const Agents& agents)
	{
		Converter_Action converter{propositions_lookup, general_action.get_inputs(), arguments, agents};

		const General_Action_Events& other = general_action.get_events();
		events.reserve(general_action.get_events().size());

		for (auto& general_action_event : other.events)
		{
			Event_Id id { events.size() };
			events.emplace_back(general_action_event, id, &converter, propositions_lookup, arguments);
		}
	}

	std::string Action_Events::to_compact_string() const
	{
		std::string result;
		for (auto& event : events) {
			result += "\n<<" + event.get_preconditions().to_string() + ",X,X>";
		}
		return result;
	}

	std::string Action_Events::to_string() const
	{
		std::string result;
		for (const Action_Event& event : events) {
			result += "\n" + event.to_string();
		}
		return result;
	}

	size_t Action_Events::size() const
	{
		return events.size();
	}

	const Action_Event& Action_Events::get_first_event() const
	{
		return events.front();
	}

	std::map<std::string, Event_Id> Action_Events::get_name_to_id() const
	{
		std::map<std::string, Event_Id> result;
		for (const Action_Event& action_event : events)
		{
			result.insert({ action_event.get_name(), action_event.get_id() });
		}
		return result;
	}

	std::vector<Action_Event>::const_iterator Action_Events::begin() const
	{
		return events.begin();
	}

	std::vector<Action_Event>::const_iterator Action_Events::end() const
	{
		return events.end();
	}
}