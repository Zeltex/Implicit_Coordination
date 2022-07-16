#include "General_Formula.hpp"


#include <assert.h>

namespace del
{

    General_Formula& General_Formula::operator=(General_Formula&& other) noexcept
    {
        formulas = std::move(other.formulas);
        other.formulas = {};
        return *this;
    }

    General_Formula::General_Formula(General_Formula&& other) noexcept
    {
        formulas = std::move(other.formulas);
        other.formulas = {};
    }

    General_Formula_Component* General_Formula::f_top()
    {
        formulas.emplace_back(Formula_Types::Top);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_bot()
    {
        formulas.emplace_back(Formula_Types::Bot);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_prop(General_Proposition_Instance proposition)
    {
        formulas.emplace_back(Formula_Types::Prop, std::move(proposition));
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_not(General_Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Not, formula);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_and(General_Formula_Component* input0, General_Formula_Component* input1)
    {
        formulas.emplace_back(Formula_Types::And, input0, input1);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_or(General_Formula_Component* input0, General_Formula_Component* input1)
    {
        formulas.emplace_back(Formula_Types::Or, input0, input1);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_believes(const std::string& agent, General_Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Believes, agent, formula);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_everyone_Believes(General_Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Everyone_Believes, formula);
        return &formulas.back();
    }

    General_Formula_Component* General_Formula::f_common_Knowledge(General_Formula_Component* formula)
    {
        formulas.emplace_back(Formula_Types::Common_Knowledge, formula);
        return &formulas.back();
    }

    void General_Formula::reset()
    {
        formulas.clear();
    }
}