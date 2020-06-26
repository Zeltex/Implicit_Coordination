#pragma once

#include <vector>
#include <string>

struct Proposition {
	Proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) :
		name(name), inputs(inputs) {}
	std::string name;
	std::vector<std::pair<std::string, std::string>> inputs;
};

struct val {
	val(bool b) : bval(b) {}
	val(std::string s) : sval(s), bval(false) {}

	bool bval;
	std::string sval;
};

enum class Token {
	ACTION_DEF,
	ANNOUNCE_DEF,
	DEFINE_DEF,
	DESIGNATED_EVENTS_DEF,
	DESIGNATED_WORLDS_DEF,
	DOMAIN_DEF,
	EFFECT_ADD_DEF,
	EFFECT_DELETE_DEF,
	EVENT_DEF,
	GOAL_DEF,
	INIT_DEF,
	OBJECTS_DEF,
	OBSERVABILITY_DEF,
	OWNER_DEF,
	PERCEIVABILITY_DEF,
	PRECONDITIONS_DEF,
	PROBLEM_DEF,
	PROPOSITIONS_DEF,
	REACHAbility_DEF,
	REFLEXIVITY_DEF,
	TYPES_DEF,
	WORLD_DEF,

	LBRACK,
	RBRACK,

	AND,
	OR,
	NOT,


	NAME,
	TRUTH,

	EQUALS,
};