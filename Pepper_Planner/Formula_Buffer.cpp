#include "Formula_Buffer.hpp"
#include "Formula_Converter.hpp"
#include <iostream>


namespace del
{
    Formula Formula_Buffer::get()
    {
        Formula temp = std::move(formula);
        formula = {};
        return temp;
    }

    void Formula_Buffer::push_pop_formula(const std::string& type) {
        if (formula_buffer.empty()) {
            switch (Formula_Converter::string_to_type(type)) {
            case Formula_Types::Top:    formula.f_top();                     break;
            case Formula_Types::Prop:   formula.f_prop(propositions.back()); break;
            }

        }
        else {
            switch (Formula_Converter::string_to_type(type)) {
            case Formula_Types::Top:    formula_buffer.back().push_back(formula.f_top());                     break;
            case Formula_Types::Prop:   formula_buffer.back().push_back(formula.f_prop(propositions.back())); break;
            }
        }
        propositions = {};
    }

    void Formula_Buffer::push_formula(const std::string& type) {
        formula_buffer.emplace_back();
        Formula_Types formula_type = Formula_Converter::string_to_type(type);
        formula_buffer_type.emplace_back(formula_type);
    }

    std::tuple<Formula_Types, std::vector<Formula_Id>> Formula_Buffer::pop_formula_info() {
        auto type = formula_buffer_type.back();
        auto args = std::move(formula_buffer.back());
        formula_buffer_type.pop_back();
        formula_buffer.pop_back();
        return { type, args };
    }

    void Formula_Buffer::pop_formula(const std::string& input) {
        Formula_Id id;
        auto [type, formula_args] = pop_formula_info();

        if (formula_args.empty()) {
            formula_args.push_back(formula.f_top());
        }

        switch (type) {
        case Formula_Types::Believes: id = formula.f_believes(atoms.get(input).id, formula_args[0]); break;
        }
        if (!formula_buffer.empty()) {
            formula_buffer.back().push_back(id);
        }
    }

    void Formula_Buffer::pop_formula() {
        Formula_Id id;
        auto [type, formula_args] = pop_formula_info();

        if (formula_args.empty()) {
            formula_args.push_back(formula.f_top());
        }

        switch (type) {
        case Formula_Types::Not:
        {
            id = formula.f_not(formula_args[0]);
            break;
        }
        case Formula_Types::And:
        {
            id = formula.f_and(formula_args);
            break;
        }
        case Formula_Types::Or:
        {
            id = formula.f_or(formula_args);
            break;
        }
        case Formula_Types::Believes:
        {
            // TODO - Implement
            std::cerr << "Unimplemented formula type belives\n";
            break;
        }
        case Formula_Types::Everyone_Believes:
        {
            // TODO - Implement
            std::cerr << "Unimplemented formula type everyone belives\n";
            break;
        }
        case Formula_Types::Common_Knowledge:
        {
            // TODO - implement
            std::cerr << "Unimplemented formula type common knowledge\n";
            break;
        }
        }
        if (!formula_buffer.empty()) {
            formula_buffer.back().push_back(id);
        }
    }
}