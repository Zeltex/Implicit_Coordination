#include "Formula.hpp"

namespace del {
	std::string Formula::to_string() const {
		return formulas[root.id].to_string(formulas);
	}
	bool Formula::valuate(const std::unordered_set<std::string> propositions) const {
		return formulas[root.id].valuate(propositions, formulas);
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

    Formula_Id Formula::f_prop(std::string prop)
    {
        formulas.emplace_back(Formula_Types::Prop, prop);
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

    Formula_Id Formula::f_believes(Agent_Id agent, Formula_Id formula)
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