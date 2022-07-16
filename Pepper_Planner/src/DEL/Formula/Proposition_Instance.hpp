#pragma once

#include <map>
#include <string>

#include "Formula_Core.hpp"
#include "Formula_Types.hpp"

namespace del
{
    class Atom;
    class Atom_Arguments;
    class Atom_Lookup;
    class Atoms;
    class Domain;
    class General_Proposition_Instance;

    struct Proposition_Instance {
        Proposition_Instance();
        Proposition_Instance(const General_Proposition_Instance* general_instance, const std::map<std::string, const Atom*>& converter);
        Proposition_Instance(const General_Proposition_Instance& general_instance, const Atom_Lookup& atom_lookup);
        Proposition_Instance(const std::string& name, const Atoms& input, size_t id);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);
        Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4);
        Proposition_Instance(const std::string& name, const Atom* arg_0, const Atom* arg_1, const Atom* arg_2, const Atom* arg_3, const Atom* arg_4);
        std::string to_string() const;
        std::string to_hash() const;
        bool operator==(const Proposition_Instance& other) const;
        bool operator!=(const Proposition_Instance& other) const;
        bool operator<(const Proposition_Instance& other) const;

    private:

        void flood_null(size_t counter);
        size_t id = EMPTY_INDEX;
        std::string name;
        std::array<const Atom*, PROPOSITION_LENGTH> arguments;
    };
}