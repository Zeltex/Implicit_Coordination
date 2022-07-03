#include "Formula.hpp"

#include "Converter.hpp"

#include <assert.h>

namespace del {

    Formula::Formula(const Formula& other, const Converter& general_to_ground) 
    {
        formulas.resize(other.formulas.size());
        if (other.formulas.empty())
        {
            return;
        }

        other.formulas.back().copy(this, general_to_ground);
    }


    Formula& Formula::operator=(Formula&& other) noexcept
    {
        formulas = std::move(other.formulas);
        other.formulas = {};
        return *this;
    }
    
    Formula::Formula(Formula&& other)
    {
        formulas = std::move(other.formulas);
        other.formulas = {};
    }

    void Formula::reset()
    { 
        formulas = {}; 
    }

    std::string Formula::to_string(const Domain& domain) const {
        if (formulas.empty()) {
            return Formula_Converter::type_to_string(Formula_Types::Top);
        } else {
            return formulas.back().to_string(domain);
        }
    }

    bool Formula::valuate_plausability(const Propositions& propositions) const
    {
        if (formulas.empty())
        {
            return true;
        }
        else
        {
            return formulas.back().valuate_plausability(propositions);
        }
    }

	bool Formula::valuate(const World_Id& world_id, const Domain& domain, const State& state) const {
        if (formulas.empty()) 
        {
            return true;
        }  
        else 
        {
            return formulas.back().valuate(world_id, domain, state);
        }
	}

    Formula_Component* Formula::f_top()
    {
        formulas.emplace_back(Formula_Types::Top);
        return &formulas.back();
    }

    Formula_Component* Formula::f_bot()
    {
        formulas.emplace_back(Formula_Types::Bot);
        return &formulas.back();
    }

    Formula_Component* Formula::f_prop(Proposition proposition)
    {
        formulas.emplace_back(Formula_Types::Prop, proposition);
        return &formulas.back();
    }

    Formula_Component* Formula::f_not(Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Not, formula);
        return &formulas.back();
    }

    Formula_Component* Formula::f_and(Formula_Component* input0, Formula_Component* input1)
    {
        formulas.emplace_back(Formula_Types::And, input0, input1);
        return &formulas.back();
    }

    Formula_Component* Formula::f_or(Formula_Component* input0, Formula_Component* input1)
    {
        formulas.emplace_back(Formula_Types::Or, input0, input1);
        return &formulas.back();
    }

    Formula_Component* Formula::f_believes(const Agent_Id& agent, Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Believes, agent, formula);
        return &formulas.back();
    }

    Formula_Component* Formula::f_everyone_Believes(Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Everyone_Believes, formula);
        return &formulas.back();
    }

    Formula_Component* Formula::f_common_Knowledge(Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Common_Knowledge, formula);
        return &formulas.back();
    }
}