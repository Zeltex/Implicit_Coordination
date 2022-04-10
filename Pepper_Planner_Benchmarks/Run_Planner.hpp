#pragma once
#include "DEL_Interface.hpp"

#include <string>
namespace del {
	void find_and_execute(std::string file_name, const std::string& planning_agent);
	void execute(DEL_Interface& del_interface);
}