#pragma once

#include <iostream>

#include "../Domain_Loader/Domain_Interface.hpp"
#include "General_Action.hpp"

namespace del {

	class Domain_Interface_Implementation : public Domain_Interface {
	public:
		Domain_Interface_Implementation() : working(false) {}
		virtual void set_debug_working() override;
		virtual void new_domain(std::string name) override;
		virtual void finish_domain() override;
		virtual void new_action(std::string name) override;
		virtual void finish_action() override;
		virtual void add_action_input(std::string type, std::string name) override;
		virtual void set_action_owner(std::string name) override;
		virtual void new_action_preconditions() override;
		virtual void finish_action_preconditions() override;
		virtual void new_event(std::string name) override;
		virtual void finish_event() override;
		virtual void start_preconditions() override;
		virtual void finish_preconditions() override;
		virtual void start_delete_list() override;
		virtual void finish_delete_list(std::vector<std::string> add_list) override;
		virtual void start_add_list() override;
		virtual void finish_add_list(std::vector<std::string> add_list) override;

		virtual void create_event(std::string name, std::string formula, std::vector<std::string> add_list, std::vector<std::string> delete_list) override;
	private:
		General_Action current_action;

		bool working;
		std::string current_domain_name;
	};
}