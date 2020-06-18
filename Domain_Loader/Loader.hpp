#pragma once

#include <string>
#include <iostream>

#include "Domain_Interface.hpp"
#include "Maepl.hpp"
#include "Domain_Buffer.hpp"

class Loader {
public:
	void parse(Domain_Interface* domain, std::string file_path);
private:
};