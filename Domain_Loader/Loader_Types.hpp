#pragma once

#include <vector>
#include <string>

namespace del {
    struct General_Proposition {
        General_Proposition(std::string name, std::vector<std::pair<std::string, std::string>> inputs) :
                name(name), inputs(inputs) {}
        std::string name;
        std::vector<std::pair<std::string, std::string>> inputs;
    };

    struct val {
        val(size_t i) : ival(i), bval(false) {}
        val(bool b) : ival(0), bval(b) {}
        val(std::string s) : ival(0), sval(s), bval(false) {}

        size_t ival;
        bool bval;
        std::string sval;
    };

    enum class Token {
        ACTION_DEF,
        ANNOUNCE_DEF,
        COST_DEF,
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
        OWNER_DEF,
        PRECONDITIONS_DEF,
        PROBLEM_DEF,
        PROPOSITIONS_DEF,
        REACHABILITY_DEF,
        REFLEXIVITY_DEF,
        REST_DEF,
        TYPES_DEF,
        WORLD_DEF,

        LBRACK,
        RBRACK,

        AND,
        OR,
        NOT,
        TOP,
        BELIEVES,

        INTEGER,
        NAME,
        TRUTH,

        EQUALS,
    };
}
