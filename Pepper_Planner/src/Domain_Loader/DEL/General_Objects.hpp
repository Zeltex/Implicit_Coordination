#pragma once
#include <map>
#include <string>
#include <vector>
#include "Formula_Types.hpp"

namespace del {
    
    class General_Agents;
    class Variables_Buffer;
    class General_Objects
    {
    friend class Atom_Lookup;
    public:
        void add(const std::string& type, Variables_Buffer& variables_buffer, General_Agents& agents);
        Atom_Id get_atom_id(const std::string& name) const;
        const std::map<std::string, Atom_Id>& get_atom_name_to_id() const;
        std::vector<Atom_Id> convert_to_atoms(const std::vector<std::string>& variables) const;
        size_t size() const;
    private:
        std::map<std::string, std::vector<std::string>> objects;
        std::map<std::string, Atom_Id> atom_name_to_id;
    };
}