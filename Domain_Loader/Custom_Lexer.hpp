#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Loader_Types.hpp"

namespace del {
    class Custom_Lexer {
    public:
        Custom_Lexer(const std::string& file_path);
        std::vector<Token> tokens;
        std::vector<size_t> line_numbers;
        std::unordered_map<size_t, val> values;
    private:

        size_t line_number;

        void handle_def(const std::string& line, size_t& pointer);
        bool matches_pattern(const std::string& line, size_t& pointer);
        size_t get_end_of_name(const std::string& line, const size_t& pointer) const;
        size_t get_end_of_integer(const std::string& line, const size_t& pointer) const;
        void add_token(const Token& token);

    };
}
