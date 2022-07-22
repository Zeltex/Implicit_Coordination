#pragma once

#include "Formula_Types.hpp"
#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance.hpp"

#include <set>
#include <vector>

namespace del {

    class Converter_Base;
    class Proposition_Instance_Buffer;

    class Propositions
    {
    public:
        struct Comparator
        {
            bool operator()(const Proposition_Instance* lhs, const Proposition_Instance* rhs) const
            {
                return lhs->get_id() < rhs->get_id();
            }
        };

        Propositions(const Propositions& other, const Propositions& delete_list, const Propositions& add_list);
        Propositions(const std::vector<General_Proposition_Instance>& other, const Converter_Base* converter);
        Propositions(const Proposition_Instance_Buffer& other, const Converter_Base* converter);
        Propositions(const Propositions& data_in);
        Propositions(std::set<const Proposition_Instance*, Comparator> data_in);

        Propositions    combine(const Propositions& other) const;
        bool            contains(const Proposition_Instance* proposition) const;
        size_t          size() const;
        std::string     to_hash() const;
        std::string     to_string() const;
        std::string     to_signature_string() const;

        std::set<const Proposition_Instance*, Comparator>::const_iterator begin() const;
        std::set<const Proposition_Instance*, Comparator>::const_iterator end() const;
        bool operator!=(const Propositions& other) const;

    private:
        std::set<const Proposition_Instance*, Comparator> propositions;

    };
}
