#pragma once

#include "Formula_Types.hpp"
#include "General_Proposition_Instance.hpp"

#include <set>
#include <vector>

namespace del {

    class Atom_Lookup;
    class Atoms;
    class Converter_Base;
    class Proposition_Instance_Buffer;
    class Domain;
    class Propositions_Lookup;
    struct Proposition_Instance;

    class Propositions
    {
    public:
        Propositions();

        Propositions(const std::vector<General_Proposition_Instance>& other, const Converter_Base* converter);
        Propositions(const Proposition_Instance_Buffer& other, const Converter_Base* converter);
        Propositions(const Propositions& data_in);
        void insert(const Propositions& propositions);
        void insert(const Proposition_Instance* proposition);
        void remove(const Propositions& propositions);
        bool contains(const Proposition_Instance* proposition) const;
        std::string to_string() const;
        std::string to_signature_string() const;
        size_t size() const;
        bool operator!=(const Propositions& other) const;
        std::string to_hash() const;

        std::set<const Proposition_Instance*> propositions;
    private:
    };
}
