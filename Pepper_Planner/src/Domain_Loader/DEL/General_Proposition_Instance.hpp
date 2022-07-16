#pragma once

#include "Formula_Core.hpp"

#include <string>

namespace del
{
    class Variables_Buffer;

	class General_Proposition_Instance
	{
        friend struct Proposition_Instance;
    public:
        General_Proposition_Instance();
        General_Proposition_Instance(const std::string& name, const std::string& arg_0);
        General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1);
        General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2);
        General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3);
        General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4);
        General_Proposition_Instance(const std::string& name, Variables_Buffer& variables);
        bool contains_non_atom_entry() const;
        const std::string get_name() const;
        bool operator==(const General_Proposition_Instance& other) const;
        
    private:
        std::string name;
        std::array<std::string, PROPOSITION_LENGTH> arguments;
	};
}