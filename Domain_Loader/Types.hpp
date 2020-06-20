#pragma once

#include <vector>
#include <string>

struct Proposition {
	Proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) :
		name(name), inputs(inputs) {}
	std::string name;
	std::vector<std::pair<std::string, std::string>> inputs;
};

struct Proposition_Instance {
	Proposition_Instance(std::string name, std::vector<std::string> arguments) :
		name(name), arguments(arguments) {}
	std::string name;
	std::vector<std::string> arguments;
};