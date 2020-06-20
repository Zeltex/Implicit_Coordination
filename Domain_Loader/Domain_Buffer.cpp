#include "Domain_Buffer.hpp"

void Domain_Buffer::set_event_name(std::string name) {
	event_name = name;
}

void  Domain_Buffer::add_event_add(std::string proposition) {
	event_add_list.insert(proposition);
}

void Domain_Buffer::add_event_delete(std::string proposition) {
	event_delete_list.insert(proposition);
}

void Domain_Buffer::add_action_input(std::string type, std::string name) {
    action_inputs.emplace_back(type, name);
}

void Domain_Buffer::add_input(std::string type, std::string name) {
    inputs.emplace_back(type, name);
}

std::string Domain_Buffer::get_event_name() {
	return event_name;
}

Formula Domain_Buffer::get_event_preconditions() {
    Formula temp = std::move(formula);
    formula = Formula();
	return std::move(temp);
}

std::unordered_set<std::string> Domain_Buffer::get_event_add_list() {
    auto temp = std::move(event_add_list);
    event_add_list = std::unordered_set<std::string>();
    return std::move(temp);
}

std::unordered_set<std::string> Domain_Buffer::get_event_delete_list() {
    auto temp = std::move(event_delete_list);
    event_delete_list = std::unordered_set<std::string>();
    return std::move(temp);
}

std::vector<std::string> Domain_Buffer::get_designated_events() {
    auto temp = std::move(designated_events);
    designated_events = std::vector<std::string>();
    return std::move(temp);
}

std::vector<std::pair<std::string, std::string>> Domain_Buffer::get_action_inputs() {
    auto temp = std::move(action_inputs);
    action_inputs = std::vector<std::pair<std::string, std::string>>();
    return std::move(temp);
}

std::vector<std::pair<std::string, std::string>> Domain_Buffer::get_inputs() {
    auto temp = std::move(inputs);
    inputs = std::vector<std::pair<std::string, std::string>>();
    return std::move(temp);
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
	event_add_list = variable_list;
	variable_list.clear();
}

void Domain_Buffer::push_event_delete_list() {
	event_delete_list = variable_list;
	variable_list.clear();
}
void Domain_Buffer::push_pop_formula(std::string type, std::string argument) {
    if (formula_buffer.empty()) {
        switch (Formula_Converter::string_to_type(type)) {
        case Formula_Types::Prop:
        {
            formula.f_prop(argument);
            break;
        }
        case Formula_Types::Top:
        {
            formula.f_top();
            break;
        }
        }
    } else {
        switch (Formula_Converter::string_to_type(type)) {
        case Formula_Types::Prop:
        {
            formula_buffer.back().push_back(formula.f_prop(argument));
            break;
        }
        case Formula_Types::Top:
        {
            formula_buffer.back().push_back(formula.f_top());
            break;
        }
        }
    }
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


void Domain_Buffer::add_designated_event(std::string event) {
    designated_events.push_back(event);
}

void Domain_Buffer::clear_designated_events() {
    designated_events.clear();
}