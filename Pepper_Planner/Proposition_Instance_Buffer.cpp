#include "Proposition_Instance_Buffer.hpp"

#include "Atom_Lookup.hpp"
#include "Inputs_Buffer.hpp"
#include "Propositions.hpp"
#include "Propositions_Lookup.hpp"

namespace del
{
    void Proposition_Instance_Buffer::set(Proposition_Instance_Buffer& other)
    {
        proposition_instances = other.proposition_instances;
        instance_to_proposition = other.instance_to_proposition;
        propositions = other.propositions;
    }

    void Proposition_Instance_Buffer::add(const std::string& name, Variables_Buffer& variables_buffer, const Inputs& inputs)
    {
        std::vector<std::string> variables = variables_buffer.get();
        std::vector<Atom_Id> temp_atoms = inputs.convert_to_atoms(variables);
        auto proposition_instance = Proposition_Instance(name, temp_atoms);
        proposition_instances.push_back(proposition_instance);
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

    std::vector<Proposition_Instance> Proposition_Instance_Buffer::get()
    {
        std::vector<Proposition_Instance> temp = std::move(proposition_instances);
        propositions = {};
        return temp;
    }

    Proposition Proposition_Instance_Buffer::to_proposition(const Proposition_Instance& proposition_instance) const
    {
        return instance_to_proposition.at(proposition_instance);
    }

    std::map<Proposition, Proposition> Proposition_Instance_Buffer::create_converter(const Propositions_Lookup& propositions_lookup) const
    {
        std::map<Proposition, Proposition> result;
        for (const auto& [instance, proposition] : instance_to_proposition)
        {
            result.insert({ proposition, propositions_lookup.get(instance) });
        }
        return result;
    }

    //Propositions Proposition_Instance_Buffer::get()
    //{
    //    Propositions temp = std::move(propositions);
    //    propositions = {};
    //    return temp;
    //}
}