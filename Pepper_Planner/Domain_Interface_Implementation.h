#pragma once

#include <iostream>
#include <unordered_set>

#include "../Domain_Loader/Domain_Interface.hpp"
#include "General_Action.hpp"

namespace del {

	class Domain_Interface_Implementation : public Domain_Interface {
	public:
		Domain_Interface_Implementation() {}
		virtual void new_domain(std::string name) override;
		virtual void finish_domain() override;
		virtual void new_action(std::string name) override;
		virtual void finish_action() override;
		virtual void set_action_input(std::vector<std::pair<std::string, std::string>> inputs) override;
		virtual void set_action_owner(std::string name) override;

		virtual void create_event(std::string name, Formula&& preconditions, std::unordered_set<std::string> add_list, std::unordered_set<std::string> delete_list) override;
		virtual void set_designated_events(std::vector<std::string> designated_events) override;
		virtual void add_proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) override;
	private:
		General_Action current_action;
		std::vector<Proposition> propositions;
		std::string current_domain_name;
	};
}