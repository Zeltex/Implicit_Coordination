#include "Formula_Component.hpp"

#include "Converter.hpp"
#include "Domain.hpp"
#include "Formula.hpp"
#include "State.hpp"
#include "Types.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

namespace del {


    Formula_Component& Formula_Component::operator=(const Formula_Component& other)
    {
        int hej = 0;
        return *this;
    }

    Formula_Component::Formula_Component(const Formula_Component& other, const Converter& general_to_ground) 
        : type(other.type), data0(other.data0), data1(other.data1)
    {

        switch (other.type) {
        case Formula_Types::Prop:
        {
            prop = general_to_ground.convert(other.prop);
            break;
        }
        case Formula_Types::Believes:
        {
            agent = general_to_ground.convert(other.agent);
            break;
        }
        }
    }

    bool Formula_Component::valuate_plausability(const Propositions& propositions) const
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
            return ((Formula_Component*)data0)->valuate_plausability(propositions)
                && ((Formula_Component*)data1)->valuate_plausability(propositions);
        }
        case Formula_Types::Or:
        {
            return ((Formula_Component*)data0)->valuate_plausability(propositions)
                || ((Formula_Component*)data1)->valuate_plausability(propositions);
        }
        case Formula_Types::Believes:
        {
            return ((Formula_Component*)data1)->valuate_plausability(propositions);
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
            return !((Formula_Component*)data0)->valuate(world_id, domain, state);
        }
        case Formula_Types::And:
        {
            return ((Formula_Component*)data0)->valuate(world_id, domain, state)
                && ((Formula_Component*)data1)->valuate(world_id, domain, state);
        }
        case Formula_Types::Or:
        {
            return ((Formula_Component*)data0)->valuate(world_id, domain, state)
                || ((Formula_Component*)data1)->valuate(world_id, domain, state);
        }
        case Formula_Types::Believes:
        {
            // TODO - Agent is proposition, should be agent id
            std::set<World_Id> reachables = state.get_reachable_worlds(agent, world_id);
            for (const auto& reachable_world : reachables) {
                if (!((Formula_Component*)data1)->valuate(reachable_world, domain, state))
                {
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


    Formula_Component::Formula_Component(Formula_Types type, Formula_Component* input0, Formula_Component* input1) :
        type(type), data0(input0), data1(input1) 
    {
    
    }

    Formula_Component* Formula_Component::copy(Formula* formula, const Converter& general_to_ground) const
    {
        switch (type) {
        case Formula_Types::Top:
        {
            return formula->f_top();
        }
        case Formula_Types::Bot:
        {
            return formula->f_bot();
        };
        case Formula_Types::Prop:
        {
            return formula->f_prop(general_to_ground.convert(prop));
        }
        case Formula_Types::Not:
        {
            return formula->f_not(
                ((Formula_Component*)data0)->copy(formula, general_to_ground));
        }
        case Formula_Types::And:
        {
            return formula->f_and(
                ((Formula_Component*)data0)->copy(formula, general_to_ground),
                ((Formula_Component*)data1)->copy(formula, general_to_ground));
        }
        case Formula_Types::Or:
        {
            return formula->f_or(
                ((Formula_Component*)data0)->copy(formula, general_to_ground),
                ((Formula_Component*)data1)->copy(formula, general_to_ground));
        }
        case Formula_Types::Believes:
        {
            return formula->f_believes(
                general_to_ground.convert(agent),
                ((Formula_Component*)data1)->copy(formula, general_to_ground));
        }
        case Formula_Types::Everyone_Believes:
        {
            assert(false);
            return nullptr;
        }
        case Formula_Types::Common_Knowledge:
        {
            assert(false);
            return nullptr;
        }
        default:
        {
            assert(false);
            return nullptr;
        }
        }
    }

    std::string Formula_Component::to_string(const Domain& domain) const
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
            return "Not(" + ((Formula_Component*)data0)->to_string(domain) + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + ((Formula_Component*)data0)->to_string(domain) + ", " + ((Formula_Component*)data1)->to_string(domain);
        }
        case Formula_Types::Or:
        {
            return "Or(" + ((Formula_Component*)data0)->to_string(domain) + ", " + ((Formula_Component*)data1)->to_string(domain);
        }
        case Formula_Types::Believes:
        {
            return "Believes_" + agent.to_string() + "(" + ((Formula_Component*)data1)->to_string(domain) + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + ((Formula_Component*)data0)->to_string(domain) + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + ((Formula_Component*)data0)->to_string(domain) + ")";
        }
        }
        return "UNKNOWN TYPE";
    }
}
