#pragma once

#include <string>
#include <iostream>
#include <fstream>

#include "Domain_Interface.hpp"
#include "Maepl.hpp"
#include "Custom_Lexer.hpp"
#include "Custom_Parser.hpp"
#include "General_Domain.hpp"

namespace del {
    class Loader {
    public:
        Loader(const std::string& file_path);
        std::unique_ptr<General_Domain> get();
    private:
        Custom_Lexer lexer;
        Custom_Parser parser;
    };
}
