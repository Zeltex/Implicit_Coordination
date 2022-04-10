#pragma once
#include "DEL_Interface.hpp"
#include <string>

namespace del {

	DEL_Interface find_plan(const std::string& file_name, const std::string& planning_agent);
	void find_and_execute(std::string file_name, const std::string& planning_agent);
	void execute(DEL_Interface& del_interface);
	DEL_Interface find_plan2(const std::string& file_name, const std::string& planning_agent);
}