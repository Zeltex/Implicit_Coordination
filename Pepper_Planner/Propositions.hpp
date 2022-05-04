#pragma once
#include "Formula_Types.hpp"

namespace del {
    class Domain;
    class Propositions
    {
    public:
        Propositions();
        Propositions(const Propositions& data_in);
        Propositions(const std::vector<Proposition>& data_in);
        void insert(const Propositions& propositions);
        void remove(const Propositions& propositions);
        bool contains(const Proposition& proposition) const;
        std::string to_string(const Domain& domain) const;
        std::string to_signature_string() const;
        void sort();
        size_t size() const;
        bool operator!=(const Propositions& other) const;
        std::string to_hash() const;

        std::vector<Proposition> propositions;
    private:
    };
}