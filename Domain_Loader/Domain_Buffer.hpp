#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>

#include "../Formula/Formula.hpp"
#include "../Formula/Types.hpp"
#include "../Formula/Formula_Converter.hpp"
#include "Types.hpp"

using namespace del;
class Domain_Buffer {
public:
	Domain_Buffer() : state_reflexivity(false), action_reflexivity(false) {};

	void set_event_name(std::string);

	void add_designated_event(std::string);
	void add_input(std::string type, std::string name);

	void add_ordered_variable(std::string variable);
	void clear_designated_events();
	std::vector<std::string> add_reflexive_perceivability(std::string name, std::vector<std::string> agents);


	std::string															get_event_name();
	Formula																get_formula();
	std::vector<Proposition_Instance>									get_event_add_list();
	std::vector<Proposition_Instance>									get_event_delete_list();
	std::vector<std::string>											get_designated_events();
	std::vector<std::pair<std::string, std::string>>					get_inputs();
	std::unordered_set<std::string>										get_types();
	std::unordered_map<std::string, std::unordered_set<std::string>>	get_objects();
	std::vector<std::string>											get_ordered_variables(); 
	std::unordered_set<std::string>										get_variables();
	std::vector<Proposition_Instance>									get_proposition_instances();
	std::vector<std::string>											get_missing_perceivables();

	void add_variable(std::string variable);
	void clear_formula();
	void clear_variable_list();
	void push_event_add_list();
	void push_event_delete_list();
	void push_types();
	void push_objects();
	void push_proposition_instance(std::string name);

	void push_pop_formula();
	void push_formula(std::string type);
	void pop_formula();

	void set_object_type(std::string type);
	void set_state_reflexivity(bool val);
	void set_action_reflexivity(bool val);
	bool is_state_reflexive();
	bool is_action_reflexive();
private:

	std::unordered_set<std::string> types;
	std::unordered_set<std::string> variable_list;
	std::vector<std::string> ordered_variable_list;
	std::vector<std::pair<std::string, std::string>> inputs;
	std::unordered_map<std::string, std::unordered_set<std::string>> objects;
	std::string current_object_type;
	std::vector<Proposition_Instance> propositions;
	bool state_reflexivity;
	bool action_reflexivity;
	std::vector<std::string> seen_perceivability;

	// Formula stuff
	Formula formula;
	std::vector<std::vector<Formula_Id>> formula_buffer;
	std::vector<Formula_Types> formula_buffer_type;



	// Event stuff
	std::string event_name;
	std::vector<Proposition_Instance> event_add_list;
	std::vector<Proposition_Instance> event_delete_list;
	std::vector<std::string> designated_events;
};