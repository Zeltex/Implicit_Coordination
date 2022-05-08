#include "Proposition_Instance.hpp"
#include "Atoms.hpp"
#include "Domain.hpp"

namespace del
{
    Proposition_Instance::Proposition_Instance() : name(), arguments() {
        for (auto& entry : arguments) {
            entry = EMPTY_INDEX;
        }
    }

    Proposition_Instance::Proposition_Instance(const std::string& name) : name(name), arguments() {
        for (auto& entry : arguments) {
            entry = EMPTY_INDEX;
        }
    }

    Proposition_Instance::Proposition_Instance(const std::string& name, const Atoms& input) 
        : name(name), arguments() {
        size_t counter;
        for (counter = 0; counter < input.size(); counter++) {
            arguments[counter] = input[counter];
        }
        while (counter < PROPOSITION_LENGTH) {
            arguments[counter] = EMPTY_INDEX;
            counter++;
        }
    }

    Proposition_Instance::Proposition_Instance(const std::string& name, const std::vector<std::string>& input, const std::map<std::string, Atom_Id>& context) :
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

    Proposition_Instance::Proposition_Instance(const Proposition_Instance& other, const std::map<size_t, Atom_Id>& input_to_atom) :
        name(other.name), arguments() {
        size_t counter = 0;
        for (auto& entry : other.arguments) {
            auto it = input_to_atom.find(entry.id);
            if (it == input_to_atom.end()) {
                arguments[counter] = entry;
            }
            else {
                arguments[counter] = it->second;
            }
            counter++;
        }
    }

    Proposition_Instance::Proposition_Instance(const Proposition_Instance& other, const Atoms& input_arguments) :
        name(other.name), arguments() {
        size_t counter = 0;
        for (auto& entry : other.arguments) {
            if (entry == EMPTY_INDEX) {
                arguments[counter] = EMPTY_INDEX;
            }
            else {
                arguments[counter] = input_arguments[entry.id];
            }
            counter++;
        }
    }

    std::string Proposition_Instance::to_string(const Domain& domain) const {
        std::string result = name + "(";
        bool first = true;
        for (auto entry : arguments) {
            if (entry == EMPTY_INDEX) continue;
            if (first) {
                first = false;
            }
            else 
            {
                result += ", ";
            }
            result += domain.get_atom_name(entry);
        }
        return result + ")";
    }

    std::string Proposition_Instance::to_simple_string() const {
        std::string result = name + "(";
        bool first = true;
        for (auto entry : arguments) {
            if (entry == EMPTY_INDEX) continue;
            if (first) {
                first = false;
            }
            else {
                result += ", ";
            }
            result += std::to_string(entry.id);
        }
        return result + ")";
    }
    bool Proposition_Instance::operator==(const Proposition_Instance& other) const {
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
    bool Proposition_Instance::operator!=(const Proposition_Instance& other) const {
        return !(*this == other);
    }

    bool Proposition_Instance::operator < (const Proposition_Instance& other) const
    {
        return to_hash().compare(other.to_hash()) < 0;
    }

    std::string Proposition_Instance::to_hash() const {
        std::string hash = name;
        for (auto& arg : arguments) {
            if (arg != EMPTY_INDEX) hash += std::to_string(arg.id);
        }
        return hash;
    }

    bool Proposition_Instance::contains_non_atom_entry() const {
        for (auto& entry : arguments) {
            if (entry == REST_INDEX) {
                return true;
            }
        }
        return false;
    }
}