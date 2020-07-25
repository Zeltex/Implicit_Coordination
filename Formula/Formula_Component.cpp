#include "Formula_Component.hpp"

namespace del {

    Formula_Types Formula_Component::get_type() const {
        return type;
    }
    const Proposition_Instance& Formula_Component::get_proposition() const {
        return prop;
    }

    Formula_Component::Formula_Component(const Formula_Component& other, const std::unordered_map<size_t, Atom_Id>& input_to_atom, const std::unordered_map<size_t, size_t>& input_to_agent) : agent(0), formula() {
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
            this->agent = input_to_agent.at(input_to_atom.at(other.agent).id);
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
            if (input_interface == nullptr) return false;
            auto& propositions = input_interface->get_true_propositions(world_id);
            return find(propositions.begin(), propositions.end(), prop) != propositions.end();
        }
        case Formula_Types::Not:
        {
            return !all_formulas[formula.id].valuate(all_formulas, world_id, input_interface);
        }
        case Formula_Types::And:
        {
            for (auto formula : formulas) {
                if (!all_formulas[formula.id].valuate(all_formulas, world_id, input_interface)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (auto formula : formulas) {
                if (all_formulas[formula.id].valuate(all_formulas, world_id, input_interface)) {
                    return true;
                }
            }
            return false;
        }
        case Formula_Types::Believes:
        {
            if (input_interface == nullptr) return false;
            std::vector<size_t> reachables = input_interface->get_reachable_worlds(agent, world_id);
            for (auto reachable_world : reachables) {
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
            return prop.to_string(id_to_atom);
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
            return "Believes_" + std::to_string(agent) + "(" + all_formulas[formula.id].to_string(all_formulas, id_to_atom) + ")";
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