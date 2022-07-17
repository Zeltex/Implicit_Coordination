#include "Proposition_Instance_Buffer.hpp"

#include "Atom_Lookup.hpp"
#include "Propositions.hpp"
#include "Propositions_Lookup.hpp"
#include "Variables_Buffer.hpp"

#include <assert.h>
#include <cassert>

namespace del
{
    Proposition_Instance_Buffer::Proposition_Instance_Buffer()
        : proposition_instances()
    {

    }

    void Proposition_Instance_Buffer::set(Proposition_Instance_Buffer& other)
    {
        proposition_instances = other.proposition_instances;
    }


    void Proposition_Instance_Buffer::set_and_consume(Proposition_Instance_Buffer& other)
    {
        proposition_instances = std::move(other.proposition_instances);

        other.proposition_instances = {};
    }

    void Proposition_Instance_Buffer::add(const std::string& name, Variables_Buffer& variables_buffer)
    {
        General_Proposition_Instance prop_instance{ name, variables_buffer };
        if (std::find(proposition_instances.begin(), proposition_instances.end(), prop_instance) == proposition_instances.end())
        {
            proposition_instances.push_back(std::move(prop_instance));
        }
    }

    Proposition_Instance_Buffer Proposition_Instance_Buffer::move()
    {
        Proposition_Instance_Buffer other;
        other.proposition_instances = std::move(proposition_instances);

        proposition_instances = {};

        return other;
    }

    std::vector<General_Proposition_Instance> Proposition_Instance_Buffer::get()
    {
        std::vector<General_Proposition_Instance> temp = std::move(proposition_instances);
        proposition_instances = {};
        return temp;
    }
}