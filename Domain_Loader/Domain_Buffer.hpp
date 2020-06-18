#pragma once

#include <string>
#include <vector>

class Domain_Buffer {
public:
	void set_event_name(std::string);
	void set_event_preconditions(std::string);
	void add_event_add(std::string);
	void add_event_delete(std::string);
	std::string get_event_name();
	std::string get_event_preconditions();
	std::vector<std::string> get_event_add_list();
	std::vector<std::string> get_event_delete_list();

	void add_variable(std::string variable);
	void clear_formula();
	void clear_variable_list();
	void push_event_add_list();
	void push_event_delete_list();
private:

	std::vector<std::string> variable_list;

	std::string event_name;
	std::string event_preconditions;
	std::vector<std::string> event_add_list;
	std::vector<std::string> event_delete_list;
	//Formula formula;
};