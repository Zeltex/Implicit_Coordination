#include "General_Formula_Component.hpp"

#include <assert.h>

namespace del
{
    General_Formula_Component::General_Formula_Component(Formula_Types type, General_Proposition_Instance prop) :
        type(type), data0(nullptr), data1(nullptr), prop(std::move(prop)), agent()
    {
    };

    General_Formula_Component::General_Formula_Component(Formula_Types type, std::string agent, General_Formula_Component* formula) :
        type(type), data0(nullptr), data1(formula), prop(), agent(std::move(agent))
    {
    };

    General_Formula_Component::General_Formula_Component(Formula_Types type, General_Formula_Component* input0, General_Formula_Component* input1) :
        type(type), data0(input0), data1(input1)
    {

    }
}