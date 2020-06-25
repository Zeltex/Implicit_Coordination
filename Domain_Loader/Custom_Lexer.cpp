#include "Custom_Lexer.hpp"


void Custom_Lexer::lex(std::ifstream& file) {
	std::string line;
	size_t line_number = 0;
	while (std::getline(file, line)) {

		size_t pointer = 0;

		while (pointer < line.size()) {
			char c = line[pointer];
			switch (c) {
			case '(':
			case '[':
			case '{': tokens.push_back(Token::LBRACK);  pointer++;  break;
			case ')':
			case ']':
			case '}': tokens.push_back(Token::RBRACK); pointer++;  break;
			case ' ':
			case '\t': pointer++; break;
			case ',': pointer++; break;
			case '=': tokens.push_back(Token::EQUALS); pointer++;  break;
			case '_': handle_def(line, pointer, line_number); break;
			default: {
				if (matches_pattern(line, pointer)) break;
				if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) {
					size_t end_of_name = get_end_of_name(line, pointer);
					tokens.push_back(Token::NAME);
					values.insert({ tokens.size() - 1, line.substr(pointer, end_of_name - pointer) });
					pointer = end_of_name;
					break;
				}
				std::cerr << "Unknown token at line " << line_number << ": " << line.substr(pointer);
				return;
				// TODO - Return custom exception
			}
			}
		}
		line_number++;
	}
}

// TODO - Optimise with a trie like datastructure
void Custom_Lexer::handle_def(const std::string& line, size_t& pointer, const size_t& line_number) {
	pointer++;
	size_t end_of_token = get_end_of_name(line, pointer);
	std::string token = line.substr(pointer, end_of_token - pointer);
	pointer = end_of_token;

	if (token == "action")				{tokens.push_back(Token:: ACTION_DEF);				return;}
	if (token == "announce_enabled")	{tokens.push_back(Token:: ANNOUNCE_DEF);			return;}
	if (token == "designated_events")	{tokens.push_back(Token:: DESIGNATED_EVENTS_DEF);	return;}
	if (token == "designated_worlds")	{tokens.push_back(Token:: DESIGNATED_WORLDS_DEF);	return;}
	if (token == "domain")				{tokens.push_back(Token:: DOMAIN_DEF);				return;}
	if (token == "effect_add")			{tokens.push_back(Token:: EFFECT_ADD_DEF);			return;}
	if (token == "effect_delete")		{tokens.push_back(Token:: EFFECT_DELETE_DEF);		return;}
	if (token == "event")				{tokens.push_back(Token:: EVENT_DEF);				return;}
	if (token == "goal")				{tokens.push_back(Token:: GOAL_DEF);				return;}
	if (token == "initial_state")		{tokens.push_back(Token:: INIT_DEF);				return;}
	if (token == "objects")				{tokens.push_back(Token:: OBJECTS_DEF);				return;}
	if (token == "observability")		{tokens.push_back(Token:: OBSERVABILITY_DEF);		return;}
	if (token == "owner")				{tokens.push_back(Token:: OWNER_DEF);				return;}
	if (token == "perceivability")		{tokens.push_back(Token:: PERCEIVABILITY_DEF);		return;}
	if (token == "preconditions")		{tokens.push_back(Token:: PRECONDITIONS_DEF);		return;}
	if (token == "problem")				{tokens.push_back(Token:: PROBLEM_DEF);				return;}
	if (token == "propositions")		{tokens.push_back(Token:: PROPOSITIONS_DEF);		return;}
	if (token == "reachability")		{tokens.push_back(Token:: REACHAbility_DEF);		return;}
	if (token == "reflexivity")			{tokens.push_back(Token:: REFLEXIVITY_DEF);			return;}
	if (token == "types")				{tokens.push_back(Token:: TYPES_DEF);				return;}
	if (token == "world")				{tokens.push_back(Token:: WORLD_DEF);				return;}

	std::cerr << "Unknown token at line" << line_number << ": _" << token << std::endl;
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



bool Custom_Lexer::matches_pattern(const std::string& line, size_t& pointer) {
	size_t line_size = line.size();
	if (line_size >= pointer + 4 && line.substr(pointer, 4) == "true")	{ tokens.push_back(Token::TRUTH);	pointer += 4; values.insert({ tokens.size() - 1, { true } });	return true; }
	if (line_size >= pointer + 5 && line.substr(pointer, 5) == "false") { tokens.push_back(Token::TRUTH);	pointer += 5; values.insert({ tokens.size() - 1, { false } });	return true; }
	if (line_size >= pointer + 3 && line.substr(pointer, 3) == "AND")	{ tokens.push_back(Token::AND);		pointer += 3; return true; }
	if (line_size >= pointer + 2 && line.substr(pointer, 2) == "OR")	{ tokens.push_back(Token::OR);		pointer += 2; return true; }
	if (line_size >= pointer + 3 && line.substr(pointer, 3) == "NOT")	{ tokens.push_back(Token::NOT);		pointer += 3; return true; }
	return false;
}