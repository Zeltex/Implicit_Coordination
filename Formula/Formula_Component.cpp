#include "Formula_Component.hpp"
#include <algorithm>
#include <iostream>

namespace del {

    Formula_Types Formula_Component::get_type() const {
        return type;
    }
    const Proposition& Formula_Component::get_proposition() const {
        return prop;
    }

    Formula_Component::Formula_Component(const Formula_Component& other, const std::map<Proposition, Proposition>& general_to_ground): agent(0), formula() {
        this->type = other.type;
        switch (other.type) {
        case Formula_Types::Prop:
        {
            auto res = general_to_ground.find(other.prop);
            if (res == general_to_ground.end()) {
                std::cerr << "Proposition " << other.prop.to_string() << " was not found while grounding\n";
                exit(-1);
            }
            this->prop = Proposition(res->second);
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
            auto res = general_to_ground.find(other.prop);
            if (res == general_to_ground.end()) {
                std::cerr << "Agemt with atom id " << other.prop.to_string() << " was not found while grounding\n";
                exit(-1);
            }
            this->agent = Proposition(res->second);
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

    bool Formula_Component::valuate(
            const std::vector<Formula_Component>& all_formulas,
            const size_t world_id,
            const Formula_Input_Interface* input_interface
    ) const
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
            return input_interface->valuate_prop(prop, world_id);
        }
        case Formula_Types::Not:
        {
            return !all_formulas[formula.id].valuate(all_formulas, world_id, input_interface);
        }
        case Formula_Types::And:
        {
            for (const auto& formula : formulas) {
                if (!all_formulas[formula.id].valuate(all_formulas, world_id, input_interface)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (const auto& formula : formulas) {
                if (all_formulas[formula.id].valuate(all_formulas, world_id, input_interface)) {
                    return true;
                }
            }
            return false;
        }
        case Formula_Types::Believes:
        {
            std::set<size_t> reachables = input_interface->get_reachable_worlds(agent, world_id);
            for (const auto& reachable_world : reachables) {
                if (!all_formulas[formula.id].valuate(all_formulas, reachable_world, input_interface)) {
                    return false;
                }
            }
            return !reachables.empty();
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

    std::string Formula_Component::to_string(const std::vector<Formula_Component>& all_formulas, const std::unordered_map<size_t, std::string>& id_to_atom) const
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
            return "Not(" + all_formulas.at(formula.id).to_string(all_formulas, id_to_atom) + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + get_string_component(formulas, all_formulas, id_to_atom) + ")";
        }
        case Formula_Types::Or:
        {
            return "Or(" + get_string_component(formulas, all_formulas, id_to_atom) + ")";
        }
        case Formula_Types::Believes:
        {
            const auto& temp_formula = all_formulas.at(formula.id);
            return "Believes_" + agent.to_string() + "(" + all_formulas[formula.id].to_string(all_formulas, id_to_atom) + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + all_formulas[formula.id].to_string(all_formulas, id_to_atom) + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + all_formulas[formula.id].to_string(all_formulas, id_to_atom) + ")";
        }
        }
        return "UNKNOWN TYPE";
    }

    std::string Formula_Component::get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas, const std::unordered_map<size_t, std::string>& id_to_atom) const {
        std::string result;
        bool first = true;
        for (Formula_Id entry : formulas) {
            if (first) first = false;
            else result += delim;
            result += all_formulas[entry.id].to_string(all_formulas, id_to_atom);
        }
        return result;
    }
}
