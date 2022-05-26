#pragma once

#include <string>
#include <vector>
#include <map>

#include "Formula_Core.hpp"
#include "Formula_Types.hpp"

namespace del
{
    class Atom_Arguments;
    class Atom_Lookup;
    class Atoms;
    class Domain;

    struct Proposition_Instance {
        Proposition_Instance();
        //Proposition_Instance(const std::string& name);
        Proposition_Instance(const std::string& name, const Atoms& input);
        Proposition_Instance(const std::string& name, const std::vector<Atom_Id>& input);
        Proposition_Instance(const std::string& name, const std::vector<std::string>& input, const std::map<std::string, Atom_Id>& context);
        Proposition_Instance(const Proposition_Instance& other, const Atom_Arguments& input);
        Proposition_Instance(const Proposition_Instance& other, const std::map<size_t, Atom_Id>& input_to_atom);
        Proposition_Instance(const Proposition_Instance& other, const Atoms& input_arguments);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4);
        Proposition_Instance(const std::string& name, const Atom_Id& arg_0, const Atom_Id& arg_1, const Atom_Id& arg_2, const Atom_Id& arg_3, const Atom_Id& arg_4);
        std::string to_string(const Domain& domain) const;
        std::string to_simple_string() const;
        bool operator==(const Proposition_Instance& other) const;
        bool operator!=(const Proposition_Instance& other) const;
        bool operator < (const Proposition_Instance& other) const;
        std::string to_hash() const;
        bool contains_non_atom_entry() const;

        std::string name;
        prop_array arguments;
    };
}