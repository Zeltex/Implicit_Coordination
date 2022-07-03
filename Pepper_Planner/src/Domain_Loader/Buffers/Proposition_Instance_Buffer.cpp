#include "Proposition_Instance_Buffer.hpp"

#include "Atom_Lookup.hpp"
#include "General_Objects.hpp"
#include "Inputs_Buffer.hpp"
#include "Propositions.hpp"
#include "Propositions_Lookup.hpp"
#include "Variables_Buffer.hpp"

#include <assert.h>
#include <cassert>

namespace del
{
    Proposition_Instance_Buffer::Proposition_Instance_Buffer()
        : instance_to_proposition(), proposition_instances(), propositions()
    {

    }

    void Proposition_Instance_Buffer::set(Proposition_Instance_Buffer& other)
    {
        proposition_instances = other.proposition_instances;
        instance_to_proposition = other.instance_to_proposition;
        propositions = other.propositions;
    }


    void Proposition_Instance_Buffer::set_and_consume(Proposition_Instance_Buffer& other)
    {
        proposition_instances = std::move(other.proposition_instances);
        instance_to_proposition = std::move(other.instance_to_proposition);
        propositions = std::move(other.propositions);

        other.proposition_instances = {};
        other.instance_to_proposition = {};
        other.propositions = {};
    }

    void Proposition_Instance_Buffer::add(const std::string& name, Variables_Buffer& variables_buffer, const Inputs& inputs)
    {
        std::vector<std::string> variables = variables_buffer.get();
        std::vector<Atom_Id> temp_atoms = inputs.convert_to_atoms(variables);
        auto proposition_instance = Proposition_Instance(name, temp_atoms);
        proposition_instances.push_back(proposition_instance);
        if (instance_to_proposition.find(proposition_instance) == instance_to_proposition.end())
        {
            instance_to_proposition.insert({ proposition_instance, instance_to_proposition.size() });
        }
    }

    void Proposition_Instance_Buffer::add(const std::string& name, Variables_Buffer& variables_buffer, const General_Objects& general_objects)
    {
        std::vector<std::string> variables = variables_buffer.get();
        std::vector<Atom_Id> temp_atoms = general_objects.convert_to_atoms(variables);
        auto proposition_instance = Proposition_Instance(name, temp_atoms);
        proposition_instances.push_back(proposition_instance);
        if (instance_to_proposition.find(proposition_instance) == instance_to_proposition.end())
        {
            instance_to_proposition.insert({ proposition_instance, instance_to_proposition.size() });
        }
    }

    std::map<Proposition_Instance, Proposition>::const_iterator Proposition_Instance_Buffer::begin() const
    {
        return instance_to_proposition.begin();
    }
    
    std::map<Proposition_Instance, Proposition>::const_iterator Proposition_Instance_Buffer::end() const
    {
        return instance_to_proposition.end();
    }

    //void Proposition_Instance_Buffer::push_proposition_instance(const std::string name, Variables_Buffer& variables_buffer, const Inputs& inputs) {
    //    std::vector<std::string> variables = variables_buffer.get();
    //    std::vector<Atom_Id> temp_atoms;
    //    temp_atoms.reserve(variables.size());

    //    // Variable list to atom id
    //    for (const std::string& entry : variables)
    //    {
    //        Atom_Id id = (entry == REST_KEYWORD)
    //            ? Atom_Id{REST_INDEX}
    //            : Atom_Id{inputs.get_index(entry)};
    //        temp_atoms.push_back(id);
    //    }

    //    // Save proposition_instance and create proposition
    //    auto proposition_instance = Proposition_Instance(name, temp_atoms);
    //    if (instance_to_proposition.find(proposition_instance) == instance_to_proposition.end()) {
    //        instance_to_proposition.insert(std::pair(proposition_instance, Proposition(instance_to_proposition.size())));
    //    }
    //    proposition_instances.push_back(proposition_instance);
    //    //propositions.push_back(instance_to_proposition.at(proposition_instance));
    //    propositions.insert(instance_to_proposition.at(proposition_instance));
    //}

    Proposition_Instance_Buffer Proposition_Instance_Buffer::move()
    {
        Proposition_Instance_Buffer other;
        other.proposition_instances = std::move(proposition_instances);
        other.instance_to_proposition = std::move(instance_to_proposition);
        other.propositions = std::move(propositions);

        proposition_instances = {};
        instance_to_proposition = {};
        propositions = {};

        return other;
    }

    std::vector<Proposition_Instance> Proposition_Instance_Buffer::get()
    {
        std::vector<Proposition_Instance> temp = std::move(proposition_instances);
        propositions = {};
        return temp;
    }

    Proposition Proposition_Instance_Buffer::to_proposition(const Proposition_Instance& proposition_instance) const
    {
        assert(instance_to_proposition.find(proposition_instance) != instance_to_proposition.end());
        return instance_to_proposition.at(proposition_instance);
    }

    Converter Proposition_Instance_Buffer::create_converter(const Propositions_Lookup& propositions_lookup) const
    {
        Converter result;
        for (const auto& [instance, proposition] : instance_to_proposition)
        {
            result.set(proposition, propositions_lookup.get(instance));
        }
        return result;
    }
}