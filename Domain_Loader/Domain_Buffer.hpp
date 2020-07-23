#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <tuple>

#include "Formula.hpp"
#include "Formula_Types.hpp"
#include "Formula_Converter.hpp"
#include "Loader_Types.hpp"

namespace del {
    class Domain_Buffer {
    public:
        Domain_Buffer() : state_reflexivity(false), action_reflexivity(false) {};

        void set_event_name(std::string);

        void add_designated_event(std::string);
        void add_input(std::string type, std::string name);

        void add_ordered_variable(std::string variable);
        void add_edge_condition(std::tuple<std::string, std::string, Formula>&& edge_condition);
        void clear_designated_events();
        std::vector<std::string> add_reflexive_perceivability(std::string name, std::vector<std::string> agents);

        std::unordered_map<std::string, Atom_Id>							get_atom_to_id();
        Formula																get_formula();
        std::vector<std::tuple<std::string, std::string, Formula>>			get_edge_conditions();
        std::vector<Proposition_Instance>									get_event_add_list();
        std::vector<Proposition_Instance>									get_event_delete_list();
        std::string															get_event_name();
        std::vector<std::string>											get_designated_events();
        std::vector<std::pair<std::string, std::string>>					get_inputs();
        std::unordered_set<std::string>										get_types();
        std::unordered_map<std::string, std::unordered_set<std::string>>	get_objects();
        std::vector<std::string>											get_ordered_variables();
        std::unordered_set<std::string>										get_variables();
        std::vector<Proposition_Instance>									get_proposition_instances();
        std::vector<std::string>											get_missing_perceivables();

        void add_variable(std::string variable);
        void clear_seen_atoms();
        void clear_formula();
        void clear_variable_list();
        void clear_proposition_instances();
        void push_event_add_list();
        void push_event_delete_list();
        void push_types();
        void push_objects();
        void push_proposition_instance(std::string name);

        void push_pop_formula(std::string type);
        void push_formula(std::string type);
        void pop_formula();

        void set_object_type(std::string type);
        void set_state_reflexivity(bool val);
        bool is_state_reflexive();
    private:

        std::unordered_set<std::string> types;
        std::unordered_set<std::string> variable_list;
        std::vector<std::string> ordered_variable_list;
        std::vector<std::string> agents;
        std::vector<std::pair<std::string, std::string>> inputs;
        std::unordered_map<std::string, std::unordered_set<std::string>> objects;
        std::string current_object_type;
        std::vector<Proposition_Instance> propositions;
        bool state_reflexivity;
        bool action_reflexivity;
        std::vector<std::string> seen_perceivability;
        std::vector<std::tuple<std::string, std::string, Formula>> edge_conditions;

        // Formula stuff
        Formula formula;
        std::vector<std::vector<Formula_Id>> formula_buffer;
        std::vector<Formula_Types> formula_buffer_type;
        std::unordered_map<std::string, Atom_Id> atom_to_id;



        // Event stuff
        std::string event_name;
        std::vector<Proposition_Instance> event_add_list;
        std::vector<Proposition_Instance> event_delete_list;
        std::vector<std::string> designated_events;
    };
}
