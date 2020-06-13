#include "Formula_Component.hpp"

namespace del {

    bool Formula_Component::valuate(std::unordered_set<std::string>& propositions) 
    {
        switch (type) {
        case Formula_Types::Top:
        {
            return true;
        }
        case Formula_Types::Bot:
        {
            return false;
        };
        case Formula_Types::Prop:
        {
            return propositions.find(prop) != propositions.end();
        }
        case Formula_Types::Not:
        {
            return !formula->valuate(propositions);
        }
        case Formula_Types::And:
        {
            for (auto formula : formulas) {
                if (!formula->valuate(propositions)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (auto formula : formulas) {
                if (formula->valuate(propositions)) {
                    return true;
                }
            }
            return false;
        }
        case Formula_Types::Believes:
        {
            // TODO - Implement
            return false;
        }
        case Formula_Types::Everyone_Believes:
        {
            // TODO - Implement
            return false;
        }
        case Formula_Types::Common_Knowledge:
        {
            // TODO - implement
            return false;
        }
        }
        return false;
    }

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