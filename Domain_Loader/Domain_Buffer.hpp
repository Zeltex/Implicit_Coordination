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
	void set_event_preconditions(Formula formula);
	void add_event_add(std::string);
	void add_event_delete(std::string);
	std::string get_event_name();
	Formula get_event_preconditions();
	std::vector<std::string> get_event_add_list();
	std::vector<std::string> get_event_delete_list();

	void add_variable(std::string variable);
	void clear_formula();
	void clear_variable_list();
	void push_event_add_list();
	void push_event_delete_list();

	void push_pop_formula(std::string type, std::string argument);
	void push_formula(std::string type);
	void pop_formula();
private:

	std::vector<std::string> variable_list;

	// Formula stuff
	Formula formula;
	std::vector<std::vector<Formula_Id>> formula_buffer;
	std::vector<Formula_Types> formula_buffer_type;



	// Event stuff
	std::string event_name;
	std::vector<std::string> event_add_list;
	std::vector<std::string> event_delete_list;
	//Formula formula;
};