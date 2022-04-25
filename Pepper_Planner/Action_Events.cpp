#include "Action_Events.hpp"
#include "Domain.hpp"

namespace del {

	Action_Event::Action_Event(const General_Action_Event& other, Event_Id id, const std::map<Proposition, Proposition>& converter)
		: name(other.name), id(id), precondition(other.precondition, converter), proposition_add(other.proposition_add), proposition_delete(other.proposition_delete)
	{

	}

	Event_Id Action_Event::get_id() const {
		return id;
	}

	const std::vector<Proposition> Action_Event::get_add_list() const {
		return proposition_add;
	}

	const std::vector<Proposition> Action_Event::get_delete_list() const {
		return proposition_delete;
	}

	const Formula& Action_Event::get_preconditions() const {
		return precondition;
	}

	std::string Action_Event::get_name() const {
		return name;
	}

	std::string Action_Event::to_string(const Domain& domain) const {
		std::string result = "Event " + std::to_string(id.id) + ": (Preconditions: " + precondition.to_string(domain.get_id_to_atom()) + ") (Add list";
		for (auto add : proposition_add) {
			result += ", " + domain.get_proposition_instance(add).to_string(domain.get_id_to_atom());
		}
		result += ") (Delete list, ";
		for (auto delete_entry : proposition_delete) {
			result += ", " + domain.get_proposition_instance(delete_entry).to_string(domain.get_id_to_atom());
		}
		result += ")";
		return result;
	}

	Action_Events::Action_Events()
	{

	}

	Action_Events::Action_Events(const General_Action& general_action, const std::vector<Atom_Id>& arguments, const Domain& domain)
	{
		const General_Action_Events& other = general_action.get_events();
		auto converter = general_action.create_converter(domain, arguments);

		for (const General_Action_Event& general_action_event : other.events)
		{
			Event_Id id { events.size() };
			events.emplace_back(general_action_event, id, converter);
		}
	}

	std::string Action_Events::to_compact_string(const Domain& domain) const
	{
		std::string result;
		for (auto& event : events) {
			result += "\n<" + event.get_preconditions().to_string(domain.get_id_to_atom()) + ",X,X>";
		}
		return result;
	}

	std::string Action_Events::to_string(const Domain& domain) const
	{
		std::string result;
		for (const Action_Event& event : events) {
			result += "\n" + event.to_string(domain);
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