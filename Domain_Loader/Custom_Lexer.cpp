#include "Custom_Lexer.hpp"

namespace del {
    void Custom_Lexer::lex(std::ifstream& file) {
        std::string line;
        line_number = 1;
        size_t current_allocation = 300;
        tokens.reserve(current_allocation);
        line_numbers.reserve(current_allocation);
        while (std::getline(file, line)) {

            if (tokens.size() >= current_allocation) {
                current_allocation = tokens.size() * 2;
                tokens.reserve(current_allocation);
                line_numbers.reserve(current_allocation);
            }

            size_t pointer = 0;

            while (pointer < line.size()) {
                char c = line[pointer];
                switch (c) {
                    case '(':
                    case '[':
                    case '{': add_token(Token::LBRACK);  pointer++;  break;
                    case ')':
                    case ']':
                    case '}': add_token(Token::RBRACK); pointer++;  break;
                    case ' ':
                    case '\t': pointer++; break;
                    case ',': pointer++; break;
                    case '=': add_token(Token::EQUALS); pointer++;  break;
                    case '_': handle_def(line, pointer); break;
                    default: {
                        if (matches_pattern(line, pointer)) break;
                        if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
                            size_t end_of_name = get_end_of_name(line, pointer);
                            add_token(Token::NAME);
                            values.insert({ tokens.size() - 1, line.substr(pointer, end_of_name - pointer) });
                            pointer = end_of_name;
                            break;
                        } else if (c >= '0' && c <= '9') {
                            size_t end_of_integer = get_end_of_integer(line, pointer);
                            add_token(Token::INTEGER);
                            val ival = { static_cast<size_t>(std::stoul(line.substr(pointer, end_of_integer - pointer), nullptr, 0)) };
                            values.insert({ tokens.size() - 1, ival });
                            pointer = end_of_integer;
                            break;
                        }
                        std::cerr << "Unknown token at line " << line_number << ": " << line.substr(pointer);
                        exit(-1);
                        // TODO - Return custom exception
                    }
                }
            }
            line_number++;
        }
    }

    void Custom_Lexer::add_token(const Token& token) {
        line_numbers.emplace_back(line_number);
        tokens.push_back(token);
    }

// TODO - Optimise with a trie like datastructure
    void Custom_Lexer::handle_def(const std::string& line, size_t& pointer) {
        pointer++;
        size_t end_of_token = get_end_of_name(line, pointer);
        std::string token = line.substr(pointer, end_of_token - pointer);
        pointer = end_of_token;

        if (token == "action")				{add_token(Token:: ACTION_DEF);				return;}
        if (token == "announce_enabled")	{add_token(Token:: ANNOUNCE_DEF);			return;}
        if (token == "cost")				{add_token(Token:: COST_DEF);				return;}
        if (token == "designated_events")	{add_token(Token:: DESIGNATED_EVENTS_DEF);	return;}
        if (token == "designated_worlds")	{add_token(Token:: DESIGNATED_WORLDS_DEF);	return;}
        if (token == "domain")				{add_token(Token:: DOMAIN_DEF);				return;}
        if (token == "effect_add")			{add_token(Token:: EFFECT_ADD_DEF);			return;}
        if (token == "effect_delete")		{add_token(Token:: EFFECT_DELETE_DEF);		return;}
        if (token == "event")				{add_token(Token:: EVENT_DEF);				return;}
        if (token == "goal")				{add_token(Token:: GOAL_DEF);				return;}
        if (token == "initial_state")		{add_token(Token:: INIT_DEF);				return;}
        if (token == "objects")				{add_token(Token:: OBJECTS_DEF);			return;}
        if (token == "owner")				{add_token(Token:: OWNER_DEF);				return;}
        if (token == "preconditions")		{add_token(Token:: PRECONDITIONS_DEF);		return;}
        if (token == "problem")				{add_token(Token:: PROBLEM_DEF);			return;}
        if (token == "propositions")		{add_token(Token:: PROPOSITIONS_DEF);		return;}
        if (token == "reachability")		{add_token(Token:: REACHABILITY_DEF);		return;}
        if (token == "reflexivity")			{add_token(Token:: REFLEXIVITY_DEF);		return;}
        if (token == "rest")				{ add_token(Token::REST_DEF); values.insert({ tokens.size() - 1, "_" + token });	return; }
        if (token == "types")				{add_token(Token:: TYPES_DEF);				return;}
        if (token == "world")				{add_token(Token:: WORLD_DEF);				return;}

        std::cerr << "Unknown token at line" << line_number << ": _" << token << std::endl;
        exit(-1);
        // TODO - Return custom exception
    }

    size_t Custom_Lexer::get_end_of_name(const std::string& line, const size_t& pointer) const {
        size_t result = pointer + 1;
        char c = line[result];
        while ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || c == '_') {
            result++;
            if (result >= line.size()) break;
            c = line[result];
        }
        return result;
    }

    size_t Custom_Lexer::get_end_of_integer(const std::string& line, const size_t& pointer) const {
        size_t result = pointer + 1;
        char c = line[result];
        while (c >= '0' && c <= '9') {
            result++;
            if (result >= line.size()) break;
            c = line[result];
        }
        return result;
    }



    bool Custom_Lexer::matches_pattern(const std::string& line, size_t& pointer) {
        size_t line_size = line.size();
        if (line_size >= pointer + 8 && line.substr(pointer, 8) == "BELIEVES")	{ add_token(Token::BELIEVES);	pointer += 8; return true; }
        if (line_size >= pointer + 4 && line.substr(pointer, 4) == "true")		{ add_token(Token::TRUTH);		pointer += 4; values.insert({ tokens.size() - 1, { true } });	return true; }
        if (line_size >= pointer + 5 && line.substr(pointer, 5) == "false")		{ add_token(Token::TRUTH);		pointer += 5; values.insert({ tokens.size() - 1, { false } });	return true; }
        if (line_size >= pointer + 3 && line.substr(pointer, 3) == "AND")		{ add_token(Token::AND);		pointer += 3; return true; }
        if (line_size >= pointer + 2 && line.substr(pointer, 2) == "OR")		{ add_token(Token::OR);			pointer += 2; return true; }
        if (line_size >= pointer + 3 && line.substr(pointer, 3) == "NOT")		{ add_token(Token::NOT);		pointer += 3; return true; }
        if (line_size >= pointer + 3 && line.substr(pointer, 3) == "TOP")		{ add_token(Token::TOP);		pointer += 3; return true; }
        return false;
    }
}
