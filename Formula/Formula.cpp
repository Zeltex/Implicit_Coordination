#include "Formula.hpp"

#include "Converter.hpp"

namespace del {

    Formula::Formula(const Formula& other, const Converter& general_to_ground) 
    {
        this->root = other.root;
        for (const auto& entry : other.formulas) 
        {
            this->formulas.push_back(Formula_Component{ entry, general_to_ground });
        }
    }

    std::string Formula::to_string(const Domain& domain) const {
        if (formulas.empty()) {
            return Formula_Converter::type_to_string(Formula_Types::Top);
        } else {
            return formulas[root.id].to_string(formulas, domain);
        }
    }

	bool Formula::valuate(const World_Id& world_id, const Domain& domain, const State& state) const {
        if (formulas.empty()) 
        {
            return true;
        }  
        else 
        {
            return formulas[root.id].valuate(formulas, world_id, domain, state);
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

    Formula_Id Formula::f_prop(Proposition proposition) 
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

    Formula_Id Formula::f_believes(const Agent_Id& agent, Formula_Id formula)
    {
        formulas.emplace_back(Formula_Types::Believes, agent, formula);
        root = Formula_Id{ formulas.size() - 1 };
        return Formula_Id{ formulas.size() - 1 };
    }

    Formula_Id Formula::f_believes(std::string agent, Formula_Id formula, const std::unordered_map<std::string, Agent_Id>& context)
    {
        return f_believes(context.at(agent), formula);
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