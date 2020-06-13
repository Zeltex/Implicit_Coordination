#include "Formula_Creator.hpp"

namespace del {

    Formula_Component* Formula_Creator::f_top()
    {
        return new Formula_Component(Formula_Types::Top);
    }

    Formula_Component* Formula_Creator::f_bot()
    {
        return new Formula_Component(Formula_Types::Bot);
    }

    Formula_Component* Formula_Creator::f_prop(std::string prop)
    {
        return new Formula_Component(Formula_Types::Prop, prop);
    }

    Formula_Component* Formula_Creator::f_not(Formula_Component* formula)
    {
        return new Formula_Component(Formula_Types::Not, formula);
    }

    Formula_Component* Formula_Creator::f_and(std::vector<Formula_Component*> formulas)
    {
        return new Formula_Component(Formula_Types::And, formulas);
    }

    Formula_Component* Formula_Creator::f_or(std::vector<Formula_Component*> formulas)
    {
        return new Formula_Component(Formula_Types::Or, formulas);
    }

    Formula_Component* Formula_Creator::f_believes(Agent_Id agent, Formula_Component* formula)
    {
        return new Formula_Component(Formula_Types::Believes, agent, formula);
    }

    Formula_Component* Formula_Creator::f_everyone_Believes(Formula_Component* formula)
    {
        return new Formula_Component(Formula_Types::Everyone_Believes, formula);
    }

    Formula_Component* Formula_Creator::f_common_Knowledge(Formula_Component* formula)
    {
        return new Formula_Component(Formula_Types::Common_Knowledge, formula);
    }
}