#include "Formula_Component.hpp"

namespace del {


    Formula_Component::Formula_Component(const Formula_Component& other, const std::unordered_map<std::string, std::string>& input_to_atom) : agent(0), formula() {
        this->type = other.type;
        switch (other.type) {
        case Formula_Types::Prop:
        {
            this->prop = Proposition_Instance(other.prop, input_to_atom);
            break;
        }
        case Formula_Types::Not:
        {
            this->formula = other.formula;
            break;
        }
        case Formula_Types::And:
        {
            this->formulas = other.formulas;
            break;
        }
        case Formula_Types::Or:
        {
            this->formulas = other.formulas;
            break;
        }
        case Formula_Types::Believes:
        {
            this->formula = other.formula;
            break;
        }
        case Formula_Types::Everyone_Believes:
        {
            this->formula = other.formula;
            break;
        }
        case Formula_Types::Common_Knowledge:
        {
            this->formula = other.formula;
            this->agent = other.agent;
            break;
        }
        }
    }

    bool Formula_Component::valuate(const std::vector<Proposition_Instance>& propositions, const std::vector<Formula_Component>& all_formulas) const
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
            return find(propositions.begin(), propositions.end(), prop) != propositions.end();
        }
        case Formula_Types::Not:
        {
            return !all_formulas[formula.id].valuate(propositions, all_formulas);
        }
        case Formula_Types::And:
        {
            for (auto formula : formulas) {
                if (!all_formulas[formula.id].valuate(propositions, all_formulas)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (auto formula : formulas) {
                if (all_formulas[formula.id].valuate(propositions, all_formulas)) {
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

    std::string Formula_Component::to_string(const std::vector<Formula_Component>& all_formulas) const
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
            return prop.to_string();
        }
        case Formula_Types::Not:
        {
            return "Not(" + all_formulas.at(formula.id).to_string(all_formulas) + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + get_string_component(formulas, all_formulas) + ")";
        }
        case Formula_Types::Or:
        {
            return "Or(" + get_string_component(formulas, all_formulas) + ")";
        }
        case Formula_Types::Believes:
        {
            const auto& temp_formula = all_formulas.at(formula.id);
            return "Believes_" + std::to_string(agent) + "(" + all_formulas[formula.id].to_string(all_formulas) + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + all_formulas[formula.id].to_string(all_formulas) + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + all_formulas[formula.id].to_string(all_formulas) + ")";
        }
        }
        return "UNKNOWN TYPE";
    }

    std::string Formula_Component::get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas) const {
        std::string result;
        bool first = true;
        for (Formula_Id entry : formulas) {
            if (first) first = false;
            else result += delim;
            result += all_formulas[entry.id].to_string(all_formulas);
        }
        return result;
    }
}