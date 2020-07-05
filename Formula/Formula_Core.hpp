#pragma once

#include <array>

#define PROPOSITION_LENGTH 5
#define EMPTY_INDEX (size_t)-1	//4294967295

#define REST_INDEX (size_t)-2	//4294967294
#define REST_KEYWORD "_rest"

struct Atom_Id;

using prop_array = std::array<Atom_Id, PROPOSITION_LENGTH>;