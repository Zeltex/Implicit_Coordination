#pragma once

#include <string>
#include <vector>
#include <unordered_map>

struct Formula_Id {
	size_t id;
	Formula_Id() = default;
	Formula_Id(size_t id) : id(id) {}
	Formula_Id(size_t id, size_t id2) {}

	bool operator==(const Formula_Id& other) const {
		return this->id == other.id;
	}
};

enum class Formula_Types {
	Top,
	Bot,
	Prop,
	Not,
	And,
	Or,
	Believes,
	Everyone_Believes,
	Common_Knowledge
};

struct Proposition_Instance {
	Proposition_Instance() : name(), arguments() {}
	Proposition_Instance(std::string name, std::vector<std::string> arguments) :
		name(name), arguments(arguments) {}

	Proposition_Instance(const Proposition_Instance& other, const std::unordered_map<std::string, std::string>& input_to_atom) :
		name(other.name), arguments() {
		for (auto& entry : other.arguments) {
			arguments.push_back(input_to_atom.at(entry));
		}
	}

	std::string name;
	std::vector<std::string> arguments;

	std::string to_string() const {
		std::string result = name + "(";
		bool first = true;
		for (auto entry : arguments) {
			if (first) {
				first = false;
			} else {
				result += ", ";
			}
			result += entry;
		}
		return result + ")";
	}
	bool operator==(const Proposition_Instance& other) const {
		if (this->name != other.name || this->arguments.size() != other.arguments.size()) {
			return false;
		}
		for (size_t i = 0; i < this->arguments.size(); i++) {
			if (this->arguments[i] != other.arguments[i]) {
				return false;
			}
		}
		return true;
	}
};