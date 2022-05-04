#include "Propositions.hpp"
#include "Domain.hpp"

namespace del {

    Propositions::Propositions(const Propositions& other)
        :propositions(other.propositions)
    {

    }

    Propositions::Propositions()
    {

    }

    Propositions::Propositions(const std::vector<Proposition>& data_in)
    {
        propositions = data_in;
    }

    void Propositions::insert(const Propositions& other)
    {
        for (const Proposition& proposition : other.propositions) 
        {
            if (std::find(propositions.begin(), propositions.end(), proposition) == propositions.end()) 
            {
                propositions.push_back(proposition);
            }
        }
    }

    void Propositions::remove(const Propositions& other)
    {
        for (const auto& proposition : other.propositions) 
        {
            auto result = std::find(propositions.begin(), propositions.end(), proposition);
            if (result != propositions.end()) 
            {
                propositions.erase(result);
            }
        }
    }

    bool Propositions::contains(const Proposition& proposition) const
    {
        return std::find(propositions.begin(), propositions.end(), proposition) != propositions.end();
    }

    std::string Propositions::to_string(const Domain& domain) const
    {
        std::string result;
        for (const Proposition& proposition : propositions) 
        {
            result += ", " + domain.get_proposition_instance(proposition).to_string(domain.get_id_to_atom());
        }
        return result;
    }

    std::string Propositions::to_signature_string() const
    {
        std::string result;
        Propositions copy = *this;
        copy.sort();
        for (const Proposition& proposition : copy.propositions) 
        {
            result += proposition.to_string();
        }
        return result;
    }

    void Propositions::sort()
    {
        std::sort(propositions.begin(), propositions.end());
    }

    size_t Propositions::size() const
    {
        return propositions.size();
    }

    bool Propositions::operator!=(const Propositions& other) const
    {
        if (propositions.size() != other.propositions.size()) return true;
        auto props1 = propositions;
        auto props2 = other.propositions;
        std::sort(props1.begin(), props1.end());
        std::sort(props2.begin(), props2.end());

        for (size_t i = 0; i < props1.size(); i++) {
            if (props1[i] != props2[i]) return true;
        }
        return false;
    }

    std::string Propositions::to_hash() const {
        std::string hash;
        std::vector<Proposition> data_copy = propositions;
        std::sort(data_copy.begin(), data_copy.end());
        for (const Proposition& prop : data_copy) {
            hash += prop.to_hash();
        }
        return hash;
    }

}