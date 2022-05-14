#pragma once

#include <set>

namespace del {
    struct Proposition;
    class Formula_Input_Interface {
    public:
        virtual bool valuate_prop(const Proposition& prop, const size_t world_id) const = 0;
        virtual std::set<size_t> get_reachable_worlds(const Proposition& agent_id, size_t world_id) const = 0;
    private:
    };
}
