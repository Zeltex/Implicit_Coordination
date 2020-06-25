#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Domain_Interface.hpp"
#include "Maepl.hpp"
#include "Domain_Buffer.hpp"
#include "Custom_Lexer.hpp"
#include "Custom_Parser.hpp"

class Loader {
public:
	void parse(Domain_Interface* domain, std::string file_path);
private:
};