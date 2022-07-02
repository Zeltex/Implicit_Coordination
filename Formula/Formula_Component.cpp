#include "Formula_Component.hpp"

#include "Converter.hpp"
#include "Domain.hpp"
#include "State.hpp"
#include "Types.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

namespace del {

    Formula_Types Formula_Component::get_type() const {
        return type;
    }
    const Proposition& Formula_Component::get_proposition() const {
        return prop;
    }

    Formula_Component::Formula_Component(const Formula_Component& other, const Converter& general_to_ground): agent(0), formula() {
        this->type = other.type;
        switch (other.type) {
        case Formula_Types::Prop:
        {
            prop = general_to_ground.convert(other.prop);
            break;
        }
        case Formula_Types::Not:
        {
            formula = other.formula;
            break;
        }
        case Formula_Types::And:
        {
            formulas = other.formulas;
            break;
        }
        case Formula_Types::Or:
        {
            formulas = other.formulas;
            break;
        }
        case Formula_Types::Believes:
        {
            agent = general_to_ground.convert(other.agent);
            formula = other.formula;
            break;
        }
        case Formula_Types::Everyone_Believes:
        {
            formula = other.formula;
            break;
        }
        case Formula_Types::Common_Knowledge:
        {
            formula = other.formula;
            agent = other.agent;
            break;
        }
        }
    }

    bool Formula_Component::valuate_plausability(const std::vector<Formula_Component>& all_formulas, const Propositions& propositions) const
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
            return propositions.contains(prop);
        }
        case Formula_Types::Not:
        {
            return true;
        }
        case Formula_Types::And:
        {
            for (const auto& formula : formulas) {
                if (!all_formulas[formula.id].valuate_plausability(all_formulas, propositions)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (const auto& formula : formulas) {
                if (all_formulas[formula.id].valuate_plausability(all_formulas, propositions)) {
                    return true;
                }
            }
            return false;
        }
        case Formula_Types::Believes:
        {
            return all_formulas[formula.id].valuate_plausability(all_formulas, propositions);
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

    bool Formula_Component::valuate(
            const std::vector<Formula_Component>& all_formulas,
            const World_Id& world_id,
            const Domain& domain,
            const State& state) const
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
            return state.is_true(world_id, prop) || domain.is_rigid(prop);
        }
        case Formula_Types::Not:
        {
            return !all_formulas[formula.id].valuate(all_formulas, world_id, domain, state);
        }
        case Formula_Types::And:
        {
            for (const auto& formula : formulas) {
                if (!all_formulas[formula.id].valuate(all_formulas, world_id, domain, state)) {
                    return false;
                }
            }
            return formulas.size() > 0;
        }
        case Formula_Types::Or:
        {
            for (const auto& formula : formulas) {
                if (all_formulas[formula.id].valuate(all_formulas, world_id, domain, state)) {
                    return true;
                }
            }
            return false;
        }
        case Formula_Types::Believes:
        {
            // TODO - Agent is proposition, should be agent id
            std::set<size_t> reachables = state.get_reachable_worlds(agent, world_id);
            for (const auto& reachable_world : reachables) {
                if (!all_formulas[formula.id].valuate(all_formulas, reachable_world, domain, state)) {
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

    std::string Formula_Component::to_string(const std::vector<Formula_Component>& all_formulas, const Domain& domain) const
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
            return "Not(" + all_formulas.at(formula.id).to_string(all_formulas, domain) + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + get_string_component(formulas, all_formulas, domain) + ")";
        }
        case Formula_Types::Or:
        {
            return "Or(" + get_string_component(formulas, all_formulas, domain) + ")";
        }
        case Formula_Types::Believes:
        {
            const auto& temp_formula = all_formulas.at(formula.id);
            return "Believes_" + agent.to_string() + "(" + all_formulas[formula.id].to_string(all_formulas, domain) + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + all_formulas[formula.id].to_string(all_formulas, domain) + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + all_formulas[formula.id].to_string(all_formulas, domain) + ")";
        }
        }
        return "UNKNOWN TYPE";
    }

    std::string Formula_Component::get_string_component(const std::vector<Formula_Id>& formulas, const std::vector<Formula_Component>& all_formulas, const Domain& domain) const {
        std::string result;
        bool first = true;
        for (Formula_Id entry : formulas) {
            if (first) first = false;
            else result += delim;
            result += all_formulas[entry.id].to_string(all_formulas, domain);
        }
        return result;
    }
}
