#include "Formula.hpp"

namespace del {
	std::string Formula::to_string() const {
		return formulas[root.id].to_string(formulas);
	}

	bool Formula::valuate(const std::vector<std::string> propositions) const {
		return formulas[root.id].valuate(propositions, formulas);
	}

    bool Formula::valuate(const std::vector<Proposition_Instance> propositions) const {
        std::vector<std::string> temp;
        for (auto& entry : propositions) {
            temp.push_back(entry.to_string());
        }
        return valuate(temp);
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

    Formula_Id Formula::f_prop(std::string name)
    {
        formulas.emplace_back(Formula_Types::Prop, name);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_prop(Proposition_Instance proposition) {
        return f_prop(proposition.to_string());
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
}