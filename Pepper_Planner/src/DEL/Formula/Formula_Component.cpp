#include "Formula_Component.hpp"

#include "Agents.hpp"
#include "Atom_Lookup.hpp"
#include "Converter_Base.hpp"
#include "Domain.hpp"
#include "Formula.hpp"
#include "General_Formula_Component.hpp"
#include "Proposition_Instance.hpp"
#include "State.hpp"
#include "Types.hpp"

#include <algorithm>
#include <assert.h>
#include <iostream>

namespace del
{


    Formula_Component& Formula_Component::operator=(const Formula_Component& other)
    {
        type = other.type;
        data0 = other.data0;
        data1 = other.data1;
        return *this;
    }

    Formula_Component::Formula_Component(Formula& formula, const General_Formula_Component* other, const Converter_Base* converter)
    {
        type = other->type;
        switch (type)
        {
        case Formula_Types::Prop:
        {
            data0 = converter->convert(&other->prop);
            data1 = nullptr;
            break;
        }
        case Formula_Types::Not:
        {
            data0 = &formula.formulas.emplace_back(formula, other->data0, converter);
            data1 = nullptr;
            break;
        }
        case Formula_Types::And:
        {
            data0 = &formula.formulas.emplace_back(formula, other->data0, converter);
            data1 = &formula.formulas.emplace_back(formula, other->data1, converter);
            break;
        }
        case Formula_Types::Or:
        {
            data0 = &formula.formulas.emplace_back(formula, other->data0, converter);
            data1 = &formula.formulas.emplace_back(formula, other->data1, converter);
            break;
        }
        case Formula_Types::Believes:
        {
            data1 = &formula.formulas.emplace_back(formula, other->data1, converter);
            data0 = converter->convert(other->agent);
            break;
        }
        case Formula_Types::Everyone_Believes:
        case Formula_Types::Common_Knowledge:
        {
            assert(false);
        }
        case Formula_Types::Bot:
        case Formula_Types::Top:
        default:
        {
            data0 = nullptr;
            data1 = nullptr;
            return;
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
            return propositions.contains((Proposition_Instance*)data0);
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
        case Formula_Types::Common_Knowledge:
        {
            assert(false);
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
            return state.is_true(world_id, (Proposition_Instance*)data0) || domain.is_rigid((Proposition_Instance*)data0);
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
            auto agent = ((Agent*)data0)->get_id();
            for (auto& world : state.get_worlds())
            {
                if (state.is_one_reachable(agent, world_id, world.get_id())
                    && !((Formula_Component*)data1)->valuate(world.get_id(), domain, state))
                {
                    return false;
                }
            }
            return true;
        }
        case Formula_Types::Everyone_Believes:
        case Formula_Types::Common_Knowledge:
        {
            assert(false);
            return false;
        }
        }
        return false;
    }

    Formula_Component::Formula_Component(Formula_Types type, const Proposition_Instance* prop) :
        type(type), data0(prop), data1(nullptr)
    {
    };

    Formula_Component::Formula_Component(Formula_Types type, const Agent* agent, Formula_Component* formula) :
        type(type), data0(agent), data1(formula)
    {
    };

    Formula_Component::Formula_Component(Formula_Types type, Formula_Component* input0, Formula_Component* input1) :
        type(type), data0(input0), data1(input1) 
    {
    
    }

    std::string Formula_Component::to_string() const
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
            return ((Proposition_Instance*)data0)->to_string();
        }
        case Formula_Types::Not:
        {
            return "Not(" + ((Formula_Component*)data0)->to_string() + ")";
        }
        case Formula_Types::And:
        {
            return "And(" + ((Formula_Component*)data0)->to_string() + ", " + ((Formula_Component*)data1)->to_string();
        }
        case Formula_Types::Or:
        {
            return "Or(" + ((Formula_Component*)data0)->to_string() + ", " + ((Formula_Component*)data1)->to_string();
        }
        case Formula_Types::Believes:
        {
            return "Believes_" + ((Agent*)data0)->to_string() + "(" + ((Formula_Component*)data1)->to_string() + ")";
        }
        case Formula_Types::Everyone_Believes:
        {
            return "Everyone_Believes(" + ((Formula_Component*)data0)->to_string() + ")";
        }
        case Formula_Types::Common_Knowledge:
        {
            return "Common_Knowledge(" + ((Formula_Component*)data0)->to_string() + ")";
        }
        }
        return "UNKNOWN TYPE";
    }
}
