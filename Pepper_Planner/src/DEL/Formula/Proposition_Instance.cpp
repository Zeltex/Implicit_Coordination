#include "Proposition_Instance.hpp"

#include "Atom_Arguments.hpp"
#include "Atom_Lookup.hpp"
#include "Atoms.hpp"
#include "Domain.hpp"

namespace del
{
    Proposition_Instance::Proposition_Instance() : name(), arguments() {
        for (auto& entry : arguments) {
            entry = EMPTY_INDEX;
        }
    }

    //Proposition_Instance::Proposition_Instance(const std::string& name) : name(name), arguments() {
    //    for (auto& entry : arguments) {
    //        entry = EMPTY_INDEX;
    //    }
    //}

    Proposition_Instance::Proposition_Instance(const std::string& name, const std::vector<Atom_Id>& input)
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

    Proposition_Instance::Proposition_Instance(const std::string& name, const Atoms& input)
        : name(name), arguments() {
        size_t counter = 0;
        for (const Atom& atom : input)
        {
            arguments[counter] = atom.get_id();
            ++counter;
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

    Proposition_Instance::Proposition_Instance(const Proposition_Instance& other, const Atom_Arguments& input)
        : name(other.name), arguments()
    {
        size_t counter = 0;
        for (auto& entry : other.arguments) {
            if (entry == EMPTY_INDEX)
            {
                arguments[counter] = entry;
            }
            else
            {
                arguments[counter] = input.get(entry);
            }
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
                arguments[counter] = input_arguments.at(entry.id).get_id();
            }
            counter++;
        }
    }

    Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0)
        : Proposition_Instance(name, atom_lookup.get_atom(arg_0).get_id(), EMPTY_INDEX, EMPTY_INDEX, EMPTY_INDEX, EMPTY_INDEX)
    {

    }

    Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1)
        : Proposition_Instance(name, atom_lookup.get_atom(arg_0).get_id(), atom_lookup.get_atom(arg_1).get_id(), EMPTY_INDEX, EMPTY_INDEX, EMPTY_INDEX)
    {

    }

    Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
        : Proposition_Instance(name, atom_lookup.get_atom(arg_0).get_id(), atom_lookup.get_atom(arg_1).get_id(), atom_lookup.get_atom(arg_2).get_id(), EMPTY_INDEX, EMPTY_INDEX)
    {

    }

    Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
        : Proposition_Instance(name, atom_lookup.get_atom(arg_0).get_id(), atom_lookup.get_atom(arg_1).get_id(), atom_lookup.get_atom(arg_2).get_id(), atom_lookup.get_atom(arg_3).get_id(), EMPTY_INDEX)
    {

    }

    Proposition_Instance::Proposition_Instance(const Atom_Lookup& atom_lookup, const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
        : Proposition_Instance(name, atom_lookup.get_atom(arg_0).get_id(), atom_lookup.get_atom(arg_1).get_id(), atom_lookup.get_atom(arg_2).get_id(), atom_lookup.get_atom(arg_3).get_id(), atom_lookup.get_atom(arg_4).get_id())
    {

    }

    Proposition_Instance::Proposition_Instance(const std::string& name, const Atom_Id& arg_0, const Atom_Id& arg_1, const Atom_Id& arg_2, const Atom_Id& arg_3, const Atom_Id& arg_4)
        : name(name), arguments({ {arg_0, arg_1, arg_2, arg_3, arg_4} })
    {

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
            result += domain.get_atom(entry).get_name();
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