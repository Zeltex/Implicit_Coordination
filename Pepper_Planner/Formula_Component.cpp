#include "Formula_Component.hpp"

namespace del {
    std::string Formula_Component::to_string()
    {
        std::string result;

        switch (type) {
        case Formula_Types::Top:
        {
            return "TOP";
        }
        case Formula_Types::Bot:
        {
            return "BOT";
        };
        case Formula_Types::Prop:
        {
            return prop;
        }
        case Formula_Types::Not:
        {
            return "Not(" + formula->to_string() + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + get_string_component(formulas) + ")";
        }
        case Formula_Types::Or:
        {
            return "Or(" + get_string_component(formulas) + ")";
        }
        case Formula_Types::Believes:
        {
            return "Believes_" + std::to_string(agent.id) + "(" + formula->to_string() + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + formula->to_string() + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + formula->to_string() + ")";
        }
        }
        return "UNKNOWN TYPE";
    }

    std::string Formula_Component::get_string_component(const std::vector<Formula_Component*>& formulas) const {
        std::string result;
        bool first = true;
        for (Formula_Component* entry : formulas) {
            if (first) first = false;
            else result += delim;
            result += entry->to_string();
        }
        return result;
    }
}