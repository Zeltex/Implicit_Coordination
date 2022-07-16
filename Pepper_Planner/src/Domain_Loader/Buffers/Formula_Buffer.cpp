#include "Formula_Buffer.hpp"

#include "Formula_Converter.hpp"
#include "General_Agents.hpp"
#include "Proposition_Instance_Buffer.hpp"

#include <assert.h>
#include <iostream>


namespace del
{
    General_Formula Formula_Buffer::get()
    {
        General_Formula temp = std::move(formula);
        formula.reset();
        return std::move(temp);
    }

    void Formula_Buffer::push_pop_formula_top()
    {
        formula_buffer.push_back(formula.f_top());
    }

    void Formula_Buffer::push_pop_formula_prop(Proposition_Instance_Buffer& proposition_instance_buffer) {
        std::vector<General_Proposition_Instance> proposition_instances = proposition_instance_buffer.get();
        assert(proposition_instances.size() == 1);
        formula_buffer.push_back(formula.f_prop(std::move(proposition_instances.front())));
    }

    void Formula_Buffer::push_formula(const std::string& type) {
        Formula_Types formula_type = Formula_Converter::string_to_type(type);
        formula_buffer_type.push_back(formula_type);
    }

    void Formula_Buffer::pop_formula_believes(const General_Agents& general_agents, const std::string& input) {
        assert(formula_buffer_type.back() == Formula_Types::Believes);
        formula_buffer_type.pop_back();
        General_Formula_Component* data = formula_buffer.back();
        formula_buffer.pop_back();
        General_Formula_Component* new_formula = formula.f_believes(input, data);
        formula_buffer.push_back(new_formula);
    }

    void Formula_Buffer::pop_formula() {
        Formula_Types type = formula_buffer_type.back();
        formula_buffer_type.pop_back();

        assert(type != Formula_Types::Believes && type != Formula_Types::Prop && type != Formula_Types::Top);

        switch (type) {
        case Formula_Types::Not:
        {
            auto data0 = formula_buffer.back();
            formula_buffer.pop_back();
            formula_buffer.push_back(formula.f_not(data0));
            break;
        }
        case Formula_Types::And:
        {
            auto data1 = formula_buffer.back();
            formula_buffer.pop_back();
            auto data0 = formula_buffer.back();
            formula_buffer.pop_back();
            formula_buffer.push_back(formula.f_and(data0, data1));
            break;
        }
        case Formula_Types::Or:
        {
            auto data1 = formula_buffer.back();
            formula_buffer.pop_back();
            auto data0 = formula_buffer.back();
            formula_buffer.pop_back();
            formula_buffer.push_back(formula.f_or(data0, data1));
            break;
        }
        case Formula_Types::Believes:
        {
            std::cerr << "This function should never be called with Believes\n";
            assert(false);
            break;
        }
        case Formula_Types::Everyone_Believes:
        {
            // TODO - Implement
            std::cerr << "Unimplemented formula type everyone belives\n";
            assert(false);
            break;
        }
        case Formula_Types::Common_Knowledge:
        {
            // TODO - implement
            std::cerr << "Unimplemented formula type common knowledge\n";
            assert(false);
            break;
        }
        }
    }
}