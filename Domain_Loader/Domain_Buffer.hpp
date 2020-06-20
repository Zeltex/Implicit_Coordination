#pragma once

#include <string>
#include <vector>
#include <iostream>

#include "../Formula/Formula.hpp"
#include "../Formula/Types.hpp"
#include "../Formula/Formula_Converter.hpp"

using namespace del;
class Domain_Buffer {
public:
	void set_event_name(std::string);
	void add_event_add(std::string);
	void add_event_delete(std::string);

	void add_designated_event(std::string);
	void clear_designated_events();


	std::string get_event_name();
	Formula get_event_preconditions();
	std::unordered_set<std::string> get_event_add_list();
	std::unordered_set<std::string> get_event_delete_list();
	std::vector<std::string> get_designated_events();

	void add_variable(std::string variable);
	void clear_formula();
	void clear_variable_list();
	void push_event_add_list();
	void push_event_delete_list();

	void push_pop_formula(std::string type, std::string argument);
	void push_formula(std::string type);
	void pop_formula();
private:

	std::unordered_set<std::string> variable_list;

	// Formula stuff
	Formula formula;
	std::vector<std::vector<Formula_Id>> formula_buffer;
	std::vector<Formula_Types> formula_buffer_type;



	// Event stuff
	std::string event_name;
	std::unordered_set<std::string> event_add_list;
	std::unordered_set<std::string> event_delete_list;
	std::vector<std::string> designated_events;
};