#pragma once

#include <vector>
#include <string>

#include "Formula.hpp"
#include "Types.hpp"
#include "Propositions.hpp"
#include "Proposition_Instance.hpp"

namespace del
{
	class Proposition_Instance_Buffer;
	class Formula_Buffer;
	class General_Action_Event
	{
	friend class Action_Event;
	public:
		General_Action_Event(const std::string& name, Event_Id id);
		//General_Action_Event(const std::string& name, Event_Id id, Formula&& precondition, const Propositions& proposition_add, const Propositions& proposition_delete);
		void set_precondition(Formula formula);
		void set_delete_list(const std::vector<Proposition_Instance>& proposition_instances);
		void set_add_list(const std::vector<Proposition_Instance>& proposition_instances);
	private:
		std::string name;
		Event_Id id;
		Formula precondition;
		std::vector<Proposition_Instance> proposition_add;
		std::vector<Proposition_Instance> proposition_delete;
	};

	class General_Action_Events
	{
	friend class Action_Events;
	public:	
		void start(const std::string& name);
		void set_preconditions(Formula_Buffer& formula_buffer);
		void set_delete_list(Proposition_Instance_Buffer& proposition_instance_buffer);
		void set_add_list(Proposition_Instance_Buffer& proposition_instance_buffer);
		//void insert(std::string name, Formula&& preconditions, const Propositions& add_list, const Propositions& delete_list);
		size_t size() const;
	private:
		std::vector<General_Action_Event> events;
	};
}