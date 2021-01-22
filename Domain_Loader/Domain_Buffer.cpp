#include "Domain_Buffer.hpp"
#include <algorithm>

namespace del {
    void Domain_Buffer::set_event_name(std::string name) {
        event_name = name;
    }

    void Domain_Buffer::add_input(std::string type, std::string name) {
        inputs.emplace_back(type, name);
        auto it = atom_to_id.find(name);
        if (it == atom_to_id.end()) {
            atom_to_id[name] = atom_to_id.size();
        }
    }

    void Domain_Buffer::add_ordered_variable(std::string variable) {
        ordered_variable_list.push_back(variable);
    }

    void Domain_Buffer::add_edge_condition(std::tuple<std::string, std::string, Formula>&& edge_condition) {
        edge_conditions.emplace_back(std::move(edge_condition));
    }

    Atom_Id Domain_Buffer::translate_atom_to_id(const std::string& type) {
        if (atom_to_id.find(type) == atom_to_id.end()) {
            atom_to_id[type] = atom_to_id.size();
        }
        return atom_to_id[type];
    }

    void Domain_Buffer::push_proposition_instance(std::string name) {
        std::vector<Atom_Id> temp_atoms;
        temp_atoms.reserve(ordered_variable_list.size());

        // Variable list to atom id
        for (auto& entry : ordered_variable_list) {
            if (entry == REST_KEYWORD) {
                atom_to_id[REST_KEYWORD] = REST_INDEX;
            } else {
                auto it = atom_to_id.find(entry);
                if (it == atom_to_id.end()) {
                    atom_to_id[entry] = atom_to_id.size();
                }
            }
            temp_atoms.emplace_back(atom_to_id[entry]);
        }

        // Save proposition_instance and create proposition
        auto proposition_instance = Proposition_Instance(name, temp_atoms);
        if (instance_to_proposition.find(proposition_instance) == instance_to_proposition.end()) {
            instance_to_proposition.insert(std::pair(proposition_instance, Proposition(instance_to_proposition.size())));
        }

        propositions.push_back(instance_to_proposition.at(proposition_instance));

        ordered_variable_list = {};
    }

    std::string Domain_Buffer::get_event_name() {
        return event_name;
    }

    Formula Domain_Buffer::get_formula() {
        Formula temp = std::move(formula);
        formula = Formula();
        return std::move(temp);
    }

    std::vector<std::tuple<std::string, std::string, Formula>> Domain_Buffer::get_edge_conditions() {
        auto temp = std::move(edge_conditions);
        edge_conditions = std::vector<std::tuple<std::string, std::string, Formula>>();
        return std::move(temp);
    }

    std::vector<Proposition> Domain_Buffer::get_event_add_list() {
        auto temp = std::move(event_add_list);
        event_add_list = {};
        return std::move(temp);
    }

    std::vector<Proposition> Domain_Buffer::get_event_delete_list() {
        auto temp = std::move(event_delete_list);
        event_delete_list = {};
        return std::move(temp);
    }

    std::vector<std::string> Domain_Buffer::get_designated_events() {
        auto temp = std::move(designated_events);
        designated_events = std::vector<std::string>();
        return std::move(temp);
    }

    std::vector<std::pair<std::string, std::string>> Domain_Buffer::get_inputs() {
        return inputs;
    }

    std::unordered_map<std::string, std::unordered_set<std::string>> Domain_Buffer::get_objects() {
        agents = { objects["agent"].begin(), objects["agent"].end() };
        auto temp = std::move(objects);
        objects = std::unordered_map<std::string, std::unordered_set<std::string>>();
        return std::move(temp);
    }

    std::vector<std::string> Domain_Buffer::get_ordered_variables() {
        auto temp = std::move(ordered_variable_list);
        ordered_variable_list = std::vector<std::string>();
        return std::move(temp);
    }

    std::unordered_set<std::string> Domain_Buffer::get_variables() {
        auto temp = std::move(variable_list);
        variable_list = {};
        return std::move(temp);
    }

    std::unordered_set<std::string> Domain_Buffer::get_types() {
        return types;
    }

    std::vector<Proposition_Instance> Domain_Buffer::get_proposition_instances() {
        auto temp = std::move(proposition_instances);
        proposition_instances = {};
        return std::move(temp);
    }

    std::unordered_map<std::string, Atom_Id> Domain_Buffer::get_atom_to_id() {
        return atom_to_id;
    }


    const std::map<Proposition_Instance, Proposition>& Domain_Buffer::get_instance_to_proposition() const {
        return instance_to_proposition;
    }
    
    std::map<Proposition_Instance, Proposition> Domain_Buffer::get_clear_instance_to_proposition() {
        auto temp = std::move(instance_to_proposition);
        instance_to_proposition.clear();
        return std::move(temp);
    }

    std::vector<std::string> Domain_Buffer::get_missing_perceivables() {
        std::vector<std::string> result;
        for (auto agent : agents){
            if (std::find(seen_perceivability.begin(), seen_perceivability.end(), agent) == seen_perceivability.end()) {
                result.push_back(agent);
            }
        }
        return result;
    }

    std::vector<std::string> Domain_Buffer::add_reflexive_perceivability(std::string name, std::vector<std::string> agents) {
        if (std::find(agents.begin(), agents.end(), name) == agents.end()) {
            agents.push_back(name);
        }
        seen_perceivability.push_back(name);
        return agents;
    }

    void Domain_Buffer::add_variable(std::string variable) {
        variable_list.insert(variable);
    }

    void Domain_Buffer::clear_formula() {
        formula = Formula();
    }

    void Domain_Buffer::clear_variable_list() {
        variable_list.clear();
    }

    void Domain_Buffer::push_event_add_list() {
        event_add_list = std::move(propositions);
    }

    void Domain_Buffer::push_event_delete_list() {
        event_delete_list = std::move(propositions);
    }
    void Domain_Buffer::push_pop_formula(std::string type) {
        if (formula_buffer.empty()) {
            switch (Formula_Converter::string_to_type(type)) {
                case Formula_Types::Top:    formula.f_top();                     break;
                case Formula_Types::Prop:   formula.f_prop(propositions.back()); break;
            }

        } else {
            switch (Formula_Converter::string_to_type(type)) {
                case Formula_Types::Top:    formula_buffer.back().push_back(formula.f_top());                     break;
                case Formula_Types::Prop:   formula_buffer.back().push_back(formula.f_prop(propositions.back())); break;
            }
        }
        propositions = {};
    }

    void Domain_Buffer::push_formula(std::string type) {
        formula_buffer.emplace_back();
        Formula_Types formula_type = Formula_Converter::string_to_type(type);
        formula_buffer_type.emplace_back(formula_type);
    }

    std::tuple<Formula_Types, std::vector<Formula_Id>> Domain_Buffer::pop_formula_info() {
        auto type = formula_buffer_type.back();
        auto args = std::move(formula_buffer.back());
        formula_buffer_type.pop_back();
        formula_buffer.pop_back();
        return { type, args };
    }

    void Domain_Buffer::pop_formula(const std::string& input) {
        Formula_Id id;
        auto [type, formula_args] = pop_formula_info();

        if (formula_args.empty()) {
            formula_args.push_back(formula.f_top());
        }

        if (input == REST_KEYWORD) {
            atom_to_id[REST_KEYWORD] = REST_INDEX;
        } else {
            auto it = atom_to_id.find(input);
            if (it == atom_to_id.end()) {
                atom_to_id[input] = atom_to_id.size();
            }
        }

        switch (type) {
            case Formula_Types::Believes: id = formula.f_believes(atom_to_id[input].id, formula_args[0]); break;
        }
        if (!formula_buffer.empty()) {
            formula_buffer.back().push_back(id);
        }
    }

    void Domain_Buffer::pop_formula() {
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

    void Domain_Buffer::push_types() {
        types = std::move(variable_list);
        variable_list = std::unordered_set<std::string>();
    }

    void Domain_Buffer::push_objects() {
        for (auto& variable : variable_list) {
            auto it = atom_to_id.find(variable);
            if (it == atom_to_id.end()) {
                atom_to_id[variable] = atom_to_id.size();
            }
        }
        objects[current_object_type] = std::move(variable_list);
        current_object_type = "";
        variable_list = std::unordered_set<std::string>();
    }

    void Domain_Buffer::add_designated_event(std::string event) {
        designated_events.push_back(event);
    }

    void Domain_Buffer::clear_designated_events() {
        designated_events.clear();
    }

    void Domain_Buffer::set_object_type(std::string type) {
        current_object_type = type;
    }

    void Domain_Buffer::set_state_reflexivity(bool val) {
        state_reflexivity = val;
    }

    bool Domain_Buffer::is_state_reflexive() {
        return state_reflexivity;
    }

    void Domain_Buffer::clear_proposition_instances() {
        propositions = {};
    }

    void Domain_Buffer::clear_seen_atoms() {
        atom_to_id = {};
    }

    void Domain_Buffer::clear_inputs() {
        inputs = {};
    }

    Atom_Id Domain_Buffer::get_owner_input_index(const std::string& type, const std::string& name) const {
        size_t counter = 0;
        for (const auto& [in_type, in_name] : inputs) {
            if (in_type == type && in_name == name) {
                return Atom_Id{ counter };
            }
            ++counter;
        }
        std::cerr << "Owner " << type << " " << name << " is not a part of input for action\n";
        exit(-1);
    }
}
