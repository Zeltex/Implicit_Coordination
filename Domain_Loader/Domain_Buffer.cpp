#include "Domain_Buffer.hpp"

void Domain_Buffer::set_event_name(std::string name) {
    event_name = name;
}

void Domain_Buffer::add_input(std::string type, std::string name) {
    inputs.emplace_back(type, name);
}

void Domain_Buffer::add_ordered_variable(std::string variable) {
    ordered_variable_list.push_back(variable);
}

void Domain_Buffer::push_proposition_instance(std::string name) {
    propositions.emplace_back(name, std::move(ordered_variable_list));
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

std::vector<Proposition_Instance> Domain_Buffer::get_event_add_list() {
    auto temp = std::move(event_add_list);
    event_add_list = {};
    return std::move(temp);
}

std::vector<Proposition_Instance> Domain_Buffer::get_event_delete_list() {
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
    auto temp = std::move(inputs);
    inputs = {};
    return std::move(temp);
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
    auto temp = std::move(propositions);
    propositions = {};
    return std::move(temp);
}

std::vector<std::string> Domain_Buffer::get_missing_perceivables() {
    std::vector<std::string> result;
    for (auto agent : agents){
        if (find(seen_perceivability.begin(), seen_perceivability.end(), agent) == seen_perceivability.end()) {
            result.push_back(agent);
        }
    }
    return result;
}

std::vector<std::string> Domain_Buffer::add_reflexive_perceivability(std::string name, std::vector<std::string> agents) {
    if (find(agents.begin(), agents.end(), name) == agents.end()) {
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
    propositions = {};
}

void Domain_Buffer::push_event_delete_list() {
	event_delete_list = std::move(propositions);
    propositions = {};
}
void Domain_Buffer::push_pop_formula() {
    if (formula_buffer.empty()) {
        formula.f_prop(propositions[0]);
    } else {
        formula_buffer.back().push_back(formula.f_prop(propositions[0]));
    }
    propositions = {};
}

void Domain_Buffer::push_formula(std::string type) {
	formula_buffer.emplace_back();
	Formula_Types formula_type = Formula_Converter::string_to_type(type);
	formula_buffer_type.emplace_back(formula_type);
}

void Domain_Buffer::pop_formula() {
	auto type = formula_buffer_type.back();
    Formula_Id id;
    std::vector<Formula_Id> formula_args = std::move(formula_buffer.back());

    formula_buffer_type.pop_back();
    formula_buffer.pop_back();

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

void Domain_Buffer::set_action_reflexivity(bool val) {
    action_reflexivity = val;
}

bool Domain_Buffer::is_state_reflexive() {
    return state_reflexivity;
}

bool Domain_Buffer::is_action_reflexive() {
    return action_reflexivity;
}