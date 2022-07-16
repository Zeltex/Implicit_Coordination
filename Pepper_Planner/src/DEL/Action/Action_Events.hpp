#pragma once

#include <list>
#include <memory>
#include <string>
#include <unordered_set>
#include <vector>

#include "Types.hpp"
#include "Formula.hpp"
#include "General_Action_Events.hpp"
#include "General_Actions.hpp"
#include "Propositions.hpp"

namespace del {
	class Agents;
	class Atoms;
	class Converter_Base;
	class Propositions_Lookup;

	class Action_Event {
	public:
		Action_Event(const std::unique_ptr<General_Action_Event>& other, Event_Id id, const Converter_Base* converter, const Propositions_Lookup& propositions_lookup, const Atoms& arguments);

		Event_Id get_id() const;
		const Formula& get_preconditions() const;
		const Propositions& get_add_list() const;
		const Propositions& get_delete_list() const;
		std::string get_name() const;
		std::string to_string() const;

	private:
		std::string name;
		Event_Id id;
		Formula precondition;
		Propositions proposition_add;
		Propositions proposition_delete;

	};

	class Action_Events
	{
	public:
		Action_Events();
		Action_Events(const General_Action& general_action, const Atoms& arguments, const Propositions_Lookup& propositions_lookup, const Agents& agents);
		std::string to_compact_string() const;
		std::string to_string() const;
		size_t size() const;
		const Action_Event& get_first_event() const;
		std::map<std::string, Event_Id> get_name_to_id() const;
		std::vector<Action_Event>::const_iterator begin() const;
		std::vector<Action_Event>::const_iterator end() const;
	private:
		std::vector<Action_Event> events;
	};
}