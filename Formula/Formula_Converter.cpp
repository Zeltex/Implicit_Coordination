#include "Formula_Converter.hpp"
namespace del {
    std::string Formula_Converter::type_to_string(Formula_Types type) {
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
            return "Prop";
        }
        case Formula_Types::Not:
        {
            return "Not";
        }
        case Formula_Types::And:
        {
            return "And";
        }
        case Formula_Types::Or:
        {
            return "Or";
        }
        case Formula_Types::Believes:
        {
            return "Believes";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge";
        }
        }
        return "UNKNOWN TYPE";
    }

    Formula_Types Formula_Converter::string_to_type(std::string type) {
        if (type == "TOP") return Formula_Types::Top;
        if (type == "BOT") return Formula_Types::Bot;
        if (type == "Prop") return Formula_Types::Prop;
        if (type == "Not") return Formula_Types::Not;
        if (type == "And") return Formula_Types::And;
        if (type == "Or") return Formula_Types::Or;
        if (type == "Believes") return Formula_Types::Believes;
        if (type == "Everyone_Believes") return Formula_Types::Everyone_Believes;
        if (type == "Common_Knowledge") return Formula_Types::Common_Knowledge;
        return Formula_Types::Bot;
    }
}