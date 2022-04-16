#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>

#include "Formula_Core.hpp"

namespace del {
    struct Formula_Id {
        size_t id;
        Formula_Id() = default;
        Formula_Id(size_t id) : id(id) {}
        Formula_Id(size_t id, size_t id2) {}

        bool operator==(const Formula_Id& other) const {
            return this->id == other.id;
        }
    };

    enum class Formula_Types {
        Top,
        Bot,
        Prop,
        Not,
        And,
        Or,
        Believes,
        Everyone_Believes,
        Common_Knowledge
    };

    struct Atom_Id {
        size_t id;
        Atom_Id() = default;
        Atom_Id(size_t id) : id(id) {}

        bool operator==(const Atom_Id& other) const {
            return this->id == other.id;
        }
        
        bool operator!=(const Atom_Id& other) const {
            return this->id != other.id;
        }

        bool operator<(const Atom_Id& other) const {
            return this->id < other.id;
        }
    };

    struct Proposition_Instance {
        Proposition_Instance() : name(), arguments() {
            for (auto& entry : arguments) {
                entry = EMPTY_INDEX;
            }
        }
        Proposition_Instance(const std::string& name) : name(name), arguments() {
            for (auto& entry : arguments) {
                entry = EMPTY_INDEX;
            }
        }

        Proposition_Instance(const std::string& name, const std::vector<Atom_Id>& input):
                name(name), arguments() {
            size_t counter;
            for (counter = 0; counter < input.size(); counter++) {
                arguments[counter] = input[counter];
            }
            while (counter < PROPOSITION_LENGTH) {
                arguments[counter] = EMPTY_INDEX;
                counter++;
            }
        }

        Proposition_Instance(const std::string& name, const std::vector<std::string>& input, const std::unordered_map<std::string, Atom_Id>& context) :
                name(name), arguments() {
            size_t counter;
            for (counter = 0; counter < input.size(); counter++) {
                arguments[counter] = context.at(input[counter]);
            }
            while (counter < PROPOSITION_LENGTH) {
                arguments[counter] = EMPTY_INDEX;
                counter++;
            }
        }

        Proposition_Instance(const Proposition_Instance& other, const std::unordered_map<size_t, Atom_Id>& input_to_atom) :
                name(other.name), arguments() {
            size_t counter = 0;
            for (auto& entry : other.arguments) {
                auto it = input_to_atom.find(entry.id);
                if (it == input_to_atom.end()) {
                    arguments[counter] = entry;
                } else {
                    arguments[counter] = it->second;
                }
                counter++;
            }
        }

        Proposition_Instance(const Proposition_Instance& other, const std::vector<Atom_Id>& input_arguments) :
            name(other.name), arguments() {
            size_t counter = 0;
            for (auto& entry : other.arguments) {
                if (entry == EMPTY_INDEX) {
                    arguments[counter] = EMPTY_INDEX;
                } else {
                    arguments[counter] = input_arguments[entry.id];
                }
                counter++;
            }
        }

        std::string name;
        prop_array arguments;
        //std::vector<std::string> arguments;

        std::string to_string(const std::unordered_map<size_t, std::string>& id_to_atom) const {
            std::string result = name + "(";
            bool first = true;
            for (auto entry : arguments) {
                if (entry == EMPTY_INDEX) continue;
                if (first) {
                    first = false;
                } else {
                    result += ", ";
                }
                result += id_to_atom.at(entry.id);
            }
            return result + ")";
        }

        std::string to_simple_string() const{
            std::string result = name + "(";
            bool first = true;
            for (auto entry : arguments) {
                if (entry == EMPTY_INDEX) continue;
                if (first) {
                    first = false;
                } else {
                    result += ", ";
                }
                result += std::to_string(entry.id);
            }
            return result + ")";
        }
        bool operator==(const Proposition_Instance& other) const {
            if (this->name != other.name || this->arguments.size() != other.arguments.size()) {
                return false;
            }
            for (size_t i = 0; i < this->arguments.size(); i++) {
                if (this->arguments[i] != other.arguments[i]) {
                    return false;
                }
            }
            return true;
        }
        bool operator!=(const Proposition_Instance& other) const {
            return !(*this == other);
        }

        bool operator < (const Proposition_Instance& other) const
        {
            return to_hash().compare(other.to_hash()) < 0;
        }

        std::string to_hash() const {
            std::string hash = name;
            for (auto& arg : arguments) {
                if (arg != EMPTY_INDEX) hash += std::to_string(arg.id);
            }
            return hash;
        }

        bool contains_non_atom_entry() const {
            for (auto& entry : arguments) {
                if (entry == REST_INDEX) {
                    return true;
                }
            }
            return false;
        }
    };

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

    struct Propositions
    {
        Propositions()
        {

        }

        Propositions(const Proposition& data_in)
        {
            data.push_back(data_in);
        }

        Propositions(const std::vector<Proposition>& data_in)
        {
            data = data_in;
        }

        void insert(const Propositions& propositions)
        {
            for (const auto& proposition : propositions.data) {
                insert(proposition);
            }
        }

        void insert(const Proposition& proposition)
        {
            if (std::find(data.begin(), data.end(), proposition) == data.end()) {
                data.push_back(proposition);
            }
        }

        void remove(const Propositions& propositions)
        {
            for (const auto& proposition : propositions.data) {
                remove(proposition);
            }
        }

        void remove(const Proposition& proposition)
        {
            auto result = std::find(data.begin(), data.end(), proposition);
            if (result != data.end()) {
                data.erase(result);
            }
        }

        bool contains(const Proposition& proposition) const 
        {
            return std::find(data.begin(), data.end(), proposition) != data.end();
        }

        std::string to_signature_string() const
        {
            std::string result;
            Propositions copy = *this;
            copy.sort();
            for (const Proposition& proposition : copy.data) {
                result += proposition.to_string();
            }
            return result;
        }

        void sort()
        {
            std::sort(data.begin(), data.end());
        }

        size_t size() const { return data.size(); }

        bool operator!=(const Propositions& other) const
        {
            if (data.size() != other.data.size()) return true;
            auto props1 = data;
            auto props2 = other.data;
            std::sort(props1.begin(), props1.end());
            std::sort(props2.begin(), props2.end());

            for (size_t i = 0; i < props1.size(); i++) {
                if (props1[i] != props2[i]) return true;
            }
            return false;
        }
        std::string to_hash() const {
            std::string hash;
            std::vector<Proposition> data_copy = data;
            std::sort(data_copy.begin(), data_copy.end());
            for (const Proposition& prop : data_copy) {
                hash += prop.to_hash();
            }
            return hash;
        }

        std::vector<Proposition> data;
    };
}

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