#include "Domain_Buffer.hpp"

void Domain_Buffer::set_event_name(std::string name) {
	event_name = name;
}

void Domain_Buffer::set_event_preconditions(std::string formula) {
	event_preconditions = formula;
}

void  Domain_Buffer::add_event_add(std::string proposition) {
	event_add_list.push_back(proposition);
}

void Domain_Buffer::add_event_delete(std::string proposition) {
	event_delete_list.push_back(proposition);
}

std::string Domain_Buffer::get_event_name() {
	return event_name;
}

std::string Domain_Buffer::get_event_preconditions() {
	return event_preconditions;
}

std::vector<std::string> Domain_Buffer::get_event_add_list() {
	return event_add_list;
}

std::vector<std::string> Domain_Buffer::get_event_delete_list() {
	return event_delete_list;
}

void Domain_Buffer::add_variable(std::string variable) {
	variable_list.push_back(variable);
}

void Domain_Buffer::clear_formula() {
	// TODO
}

void Domain_Buffer::clear_variable_list() {
	variable_list.clear();
}

void Domain_Buffer::push_event_add_list() {
	event_add_list = variable_list;
	variable_list.clear();
}

void Domain_Buffer::push_event_delete_list() {
	event_delete_list = variable_list;
	variable_list.clear();
}

void Domain_Buffer::increment_formula_level(std::string type) {
	// TODO
}

void Domain_Buffer::push_formula() {
	// TODO
}