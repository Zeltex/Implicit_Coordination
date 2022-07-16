#pragma once

#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Formula.hpp"
#include "Formula_Buffer.hpp"
#include "Formula_Converter.hpp"
#include "General_Actions.hpp"
#include "General_Agents.hpp"
#include "General_Atoms.hpp"
#include "General_Objects.hpp"
#include "General_State.hpp"
#include "General_Typed_Propositions.hpp"
#include "Inputs_Buffer.hpp"
#include "Loader_Types.hpp"
#include "Propositions.hpp"
#include "Proposition_Instance.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "Variables_Buffer.hpp"

namespace del {
    class General_Domain {
    public:
        General_Domain() {}

        // Domain
        Variables_Buffer types;
        General_Typed_Propositions typed_propositions;
        General_Actions actions;
        bool announce_enabled = false;

        // Problem
        General_State state;
        Proposition_Instance_Buffer rigid_propositions;
        General_Formula goal;
        General_Objects objects;
        General_Agents agents;

        // Temp buffers
        General_Action_Events events_buffer;
        Inputs_Buffer inputs_buffer;
        Variables_Buffer variables_buffer;
        Formula_Buffer formula_buffer;
        Proposition_Instance_Buffer proposition_instance_buffer;
        General_Edge_Conditions edge_condition_buffer;
    };
}
