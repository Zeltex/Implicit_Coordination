#pragma once

#include <string>
#include <vector>

#include "../Formula/Formula.hpp"

class Domain_Interface {
public:
	virtual void set_debug_working() = 0;
	virtual void new_domain(std::string name) = 0;
	virtual void finish_domain() = 0;
	virtual void new_action(std::string name) = 0;
	virtual void finish_action() = 0;
	virtual void add_action_input(std::string type, std::string name) = 0; 
	virtual void set_action_owner(std::string name) = 0;
	virtual void new_action_preconditions() = 0;
	virtual void finish_action_preconditions() = 0;
	virtual void new_event(std::string name) = 0;
	virtual void finish_event() = 0;
	virtual void start_preconditions() = 0;
	virtual void finish_preconditions() = 0;
	virtual void start_delete_list() = 0;
	virtual void finish_delete_list(std::vector<std::string> add_list) = 0;
	virtual void start_add_list() = 0;
	virtual void finish_add_list(std::vector<std::string> add_list) = 0;

	virtual void create_event(std::string name, del::Formula formula, std::vector<std::string> add_list, std::vector<std::string> delete_list) = 0;
private:
	std::vector<std::string> buffer_list;
};