#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include "Types.hpp"
#include "Formula.hpp"
#include "General_Action_Events.hpp"
#include "General_Action.hpp"
#include "Propositions.hpp"

namespace del {
	class Domain;
	class Atoms;
	class Action_Event {
	public:
		Action_Event(const General_Action_Event& other, Event_Id id, const std::map<Proposition, Proposition>& converter);

		Event_Id get_id() const;
		const Formula& get_preconditions() const;
		const Propositions& get_add_list() const;
		const Propositions& get_delete_list() const;
		std::string get_name() const;
		std::string to_string(const Domain& domain) const;

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
		Action_Events(const General_Action& general_action, const Atoms& arguments, const Domain& domain);
		std::string to_compact_string(const Domain& domain) const;
		std::string to_string(const Domain& domain) const;
		size_t size() const;
		const Action_Event& get_first_event() const;
		std::map<std::string, Event_Id> get_name_to_id() const;
		std::vector<Action_Event>::const_iterator begin() const;
		std::vector<Action_Event>::const_iterator end() const;
	private:
		std::vector<Action_Event> events;
	};
}