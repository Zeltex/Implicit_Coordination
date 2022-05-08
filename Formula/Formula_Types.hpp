#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

#include "Formula_Core.hpp"

namespace del {
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

    struct Atom_Id {
        size_t id;
        Atom_Id() = default;
        Atom_Id(size_t id) : id(id) {}

        bool operator==(const Atom_Id& other) const {
            return this->id == other.id;
        }
        
        bool operator!=(const Atom_Id& other) const {
            return this->id != other.id;
        }

        bool operator<(const Atom_Id& other) const {
            return this->id < other.id;
        }
    };
}