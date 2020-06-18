#pragma once

#include <string>
#include <iostream>

#include "Domain_Interface.hpp"

class Loader {
public:
	void parse(Domain_Interface* domain, std::string file_path);
private:
};