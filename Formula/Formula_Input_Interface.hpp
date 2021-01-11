#pragma once

#include <vector>

#include "Formula_Types.hpp"

namespace del {
    class Formula_Input_Interface {
    public:
        virtual bool valuate_prop(Proposition_Instance prop, const size_t world_id) const = 0;
        virtual std::vector<size_t> get_reachable_worlds(size_t agent_id, size_t world_id) const = 0;
    private:
    };
}
