#pragma once

#include <string>
#include <vector>
#include <map>

#include "Formula_Core.hpp"
#include "Formula_Types.hpp"

namespace del
{
    class Domain;
    class Atoms;
    struct Proposition_Instance {
        Proposition_Instance();
        Proposition_Instance(const std::string& name);
        Proposition_Instance(const std::string& name, const Atoms& input);
        Proposition_Instance(const std::string& name, const std::vector<std::string>& input, const std::map<std::string, Atom_Id>& context);
        Proposition_Instance(const Proposition_Instance& other, const std::map<size_t, Atom_Id>& input_to_atom);
        Proposition_Instance(const Proposition_Instance& other, const Atoms& input_arguments);
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