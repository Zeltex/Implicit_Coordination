#include "General_Proposition_Instance.hpp"

#include "Variables_Buffer.hpp"

namespace del
{
    General_Proposition_Instance::General_Proposition_Instance()
    {

    }

    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, const std::string& arg_0)
        : General_Proposition_Instance(name, arg_0, "", "", "", "")
    {

    }
    
    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1)
        : General_Proposition_Instance(name, arg_0, arg_1, "", "", "")
    {

    }

    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
        : General_Proposition_Instance(name, arg_0, arg_1, arg_2, "", "")
    {

    }

    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
        : General_Proposition_Instance(name, arg_0, arg_1, arg_2, arg_3, "")
    {

    }

    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
        : name(name), arguments({ arg_0, arg_1, arg_2, arg_3, arg_4 })
    {

    }

    General_Proposition_Instance::General_Proposition_Instance(const std::string& name, Variables_Buffer& variables)
        : name(name)
    {
        size_t counter = 0;
        std::vector<std::string> args = variables.get();
        for (std::string& entry : args)
        {
            arguments.at(counter) = entry;
            ++counter;
        }

        for (; counter < PROPOSITION_LENGTH; ++counter)
        {
            arguments.at(counter) = "";
        }
    }

    bool General_Proposition_Instance::contains_non_atom_entry() const
    {
        for (auto& arg : arguments)
        {
            if (arg == REST_KEYWORD)
            {
                return true;
            }
        }
        return false;
    }

    const std::string General_Proposition_Instance::get_name() const
    {
        return name;
    }


    bool General_Proposition_Instance::operator==(const General_Proposition_Instance& other) const
    {
        return name == other.name && arguments == other.arguments;
    }
}