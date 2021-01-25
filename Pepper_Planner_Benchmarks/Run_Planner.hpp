#pragma once
#include <string>
namespace del {
	class DEL_Interface;
	void find_and_execute(std::string file_name, const std::string& planning_agent);
	void execute(DEL_Interface& del_interface);
}