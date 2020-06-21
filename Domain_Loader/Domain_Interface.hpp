#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "../Formula/Formula.hpp"
#include "Types.hpp"

class Domain_Interface {
public:
	virtual void new_domain(std::string name) = 0;
	virtual void finish_domain() = 0;
	virtual void finish_problem() = 0;
	virtual void new_action(std::string name) = 0;
	virtual void finish_action() = 0;
	virtual void set_action_input(std::vector<std::pair<std::string, std::string>> inputs) = 0;
	virtual void set_action_owner(std::string name) = 0;


	virtual void create_event(std::string name, del::Formula&& preconditions, std::unordered_set<std::string> add_list, std::unordered_set<std::string> delete_list) = 0;
	virtual void set_designated_events(std::vector<std::string> designated_events) = 0;
	virtual void set_types(std::unordered_set<std::string> types) = 0;
	virtual void add_proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) = 0;
	virtual void set_objects(std::unordered_map<std::string, std::unordered_set<std::string>> objects) = 0;
	virtual void set_domain(std::string domain_name) = 0;
	virtual void set_initial_state(std::vector<Proposition_Instance> propositions) = 0;
	virtual void create_world(std::string name, std::vector<Proposition_Instance> propositions) = 0;
private:
	std::vector<std::string> buffer_list;
};