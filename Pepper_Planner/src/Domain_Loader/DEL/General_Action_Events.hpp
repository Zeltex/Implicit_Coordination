#pragma once

#include <memory>
#include <string>
#include <vector>

#include "General_Formula.hpp"
#include "Types.hpp"
#include "Propositions.hpp"
#include "Proposition_Instance.hpp"
#include "Proposition_Instance_Buffer.hpp"

namespace del
{
	class Formula_Buffer;

	class General_Action_Event
	{
	friend class Action_Event;
	friend class General_Action_Events;
	public:
		General_Action_Event(const std::string& name, Event_Id id);
		void set_add_list(const std::vector<General_Proposition_Instance>& proposition_instances);
		void set_delete_list(const std::vector<General_Proposition_Instance>& proposition_instances);
		void set_instance_buffer(Proposition_Instance_Buffer& proposition_instance_buffer);
		void set_precondition(General_Formula&& formula);
	private:
		bool designated;
		std::string name;
		Event_Id id;
		General_Formula precondition;
		std::vector<General_Proposition_Instance> proposition_add;
		std::vector<General_Proposition_Instance> proposition_delete;
		Proposition_Instance_Buffer proposition_instance_buffer;
	};

	class General_Action_Events
	{
	friend class Action_Events;
	public:
		General_Action_Events();
		General_Action_Events(std::vector<std::unique_ptr<General_Action_Event>> events);
		void end(Proposition_Instance_Buffer& proposition_instance_buffer);
		std::vector<std::unique_ptr<General_Action_Event>> get();
		void start(const std::string& name);
		void set_preconditions(Formula_Buffer& formula_buffer);
		void set_delete_list(Proposition_Instance_Buffer& proposition_instance_buffer);
		void set_add_list(Proposition_Instance_Buffer& proposition_instance_buffer);
		void set_designated_events(Variables_Buffer& variables_buffer);
		size_t size() const;
	private:
		std::vector<std::unique_ptr<General_Action_Event>> events;
	};
}