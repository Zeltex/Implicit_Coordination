#include "Formula.hpp"

namespace del {

    Formula::Formula(const Formula& other, const std::unordered_map<size_t, Atom_Id>& input_to_atom) {
        this->root = other.root;
        for (const auto& entry : other.formulas) {
            this->formulas.emplace_back(entry, input_to_atom);
        }
    }

    std::string Formula::to_string(const std::unordered_map<size_t, std::string>& id_to_atom) const {
        if (formulas.empty()) {
            return Formula_Converter::type_to_string(Formula_Types::Top);
        } else {
            return formulas[root.id].to_string(formulas, id_to_atom);
        }
    }

	bool Formula::valuate(const std::vector<Proposition_Instance> propositions) const {
        if (formulas.empty()) {
            return true;
        } else {
            return formulas[root.id].valuate(propositions, formulas);
        }
	}

    Formula_Id Formula::f_top()
    {
        formulas.emplace_back(Formula_Types::Top);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_bot()
    {
        formulas.emplace_back(Formula_Types::Bot);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_prop(Proposition_Instance proposition) 
    {
        formulas.emplace_back(Formula_Types::Prop, proposition);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_not(Formula_Id formula)
    {
        formulas.emplace_back(Formula_Types::Not, formula);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_and(std::vector<Formula_Id> input_formulas)
    {
        formulas.emplace_back(Formula_Types::And, input_formulas);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_or(std::vector<Formula_Id> input_formulas)
    {
        formulas.emplace_back(Formula_Types::Or, input_formulas);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_believes(size_t agent, Formula_Id formula)
    {
        formulas.emplace_back(Formula_Types::Believes, agent, formula);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_believes(std::string agent, Formula_Id formula, std::unordered_map<std::string, size_t> context)
    {
        return f_believes(context[agent], formula);
    }

    Formula_Id Formula::f_everyone_Believes(Formula_Id formula)
    {
        formulas.emplace_back(Formula_Types::Everyone_Believes, formula);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_common_Knowledge(Formula_Id formula)
    {
        formulas.emplace_back(Formula_Types::Common_Knowledge, formula);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    const Formula_Component& Formula::get_component(Formula_Id formula) const {
        return formulas.at(formula.id);
    }
    
    const Formula_Id& Formula::get_root() const {
        return root;
    }
}