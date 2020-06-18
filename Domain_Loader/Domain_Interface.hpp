#pragma once

#include <string>

class Domain_Interface {
public:
	virtual void set_debug_working() = 0;
	virtual void new_domain(std::string name) = 0;
	virtual void finish_domain() = 0;
	virtual void new_action(std::string name) = 0;
	virtual void finish_action() = 0;
	virtual void add_action_input(std::string type, std::string name) = 0;
private:
};