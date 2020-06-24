#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#include "Types.hpp"

class Custom_Lexer {
public:
	void lex(std::ifstream& file);
private:
	void handle_def(const std::string& line, size_t& pointer, const size_t& line_number);
	bool matches_pattern(const std::string& line, size_t& pointer);
	size_t get_end_of_name(const std::string& line, const size_t& pointer) const;

	std::vector<Token> tokens;
	std::unordered_map<size_t, val> values;
};