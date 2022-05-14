#pragma once
#include "Formula_Types.hpp"

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

    class Domain;
    class Propositions
    {
    public:
        Propositions();
        Propositions(const Propositions& data_in);
        Propositions(const std::vector<Proposition>& data_in);
        void insert(const Propositions& propositions);
        void insert(const Proposition& proposition);
        void remove(const Propositions& propositions);
        bool contains(const Proposition& proposition) const;
        std::string to_string(const Domain& domain) const;
        std::string to_signature_string() const;
        void sort();
        size_t size() const;
        bool operator!=(const Propositions& other) const;
        std::string to_hash() const;
        void reserve(size_t size);

        std::vector<Proposition> propositions;
    private:
    };
}

// TODO - Can probably be removed
namespace std {
    template<>
    struct hash<del::Proposition>
    {
        size_t
            operator()(const del::Proposition& obj) const
        {
            return hash<size_t>()(obj.to_hash());
        }
    };
}