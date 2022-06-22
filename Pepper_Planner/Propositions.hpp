#pragma once

#include "Formula_Types.hpp"

#include <set>

namespace del {

    // A proposition is a name with a number of atom parameters
    // Propositions are referenced by id. Full info is stored in Domain
    struct Proposition {
    public:
        Proposition() : id(EMPTY_INDEX) {}
        Proposition(size_t id) : id(id) {}
        std::string to_string() const { return std::to_string(id); }
        size_t to_hash() const { return id; }
        bool operator==(const Proposition& other) const { return this->id == other.id; }
        bool operator!=(const Proposition& other) const { return !(*this == other); }
        bool operator<(const Proposition& other) const { return this->id < other.id; }
    private:
        size_t id;
    };

    class Atoms;
    struct Proposition_Instance_Buffer;
    class Domain;
    class Propositions_Lookup;
    struct Proposition_Instance;
    class Propositions
    {
    public:
        Propositions();
        Propositions(const Proposition_Instance_Buffer& rigid_propositions, const Propositions_Lookup& propositions_lookup);

        Propositions(const std::vector<Proposition_Instance>& other, const Propositions_Lookup& propositions_lookup, const Atoms& arguments);

        Propositions(const Propositions& data_in);
        void insert(const Propositions& propositions);
        void insert(const Proposition& proposition);
        void remove(const Propositions& propositions);
        bool contains(const Proposition& proposition) const;
        std::string to_string(const Domain& domain) const;
        std::string to_signature_string() const;
        size_t size() const;
        bool operator!=(const Propositions& other) const;
        std::string to_hash() const;

        std::set<Proposition> propositions;
    private:
    };
}
