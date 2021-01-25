#pragma once

#include <string>
#include <vector>
#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <tuple>
#include <map>

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
        std::vector<std::unordered_set<std::string>>                        get_relations();
        std::map<Proposition_Instance, Proposition>                         get_clear_instance_to_proposition();
        std::vector<std::string>											get_designated_events();
        std::vector<std::tuple<std::string, std::string, Formula>>			get_edge_conditions();
        std::vector<Proposition>									        get_event_add_list();
        std::vector<Proposition>        									get_event_delete_list();
        std::string															get_event_name();
        Formula																get_formula();
        std::vector<std::pair<std::string, std::string>>					get_inputs();
        const std::map<Proposition_Instance, Proposition>&                  get_instance_to_proposition() const;
        std::vector<std::string>											get_missing_perceivables();
        std::unordered_map<std::string, std::unordered_set<std::string>>	get_objects();
        std::vector<std::string>											get_ordered_variables();
        std::vector<Proposition_Instance>									get_proposition_instances();
        std::unordered_set<std::string>										get_types();
        std::unordered_set<std::string>										get_variables();
        Atom_Id																translate_atom_to_id(const std::string& type);

        void add_variable(std::string variable);
        void clear_relations();
        void clear_seen_atoms();
        void clear_formula();
        void clear_inputs();
        void clear_variable_list();
        void clear_proposition_instances();
        void push_relations();
        void push_event_add_list();
        void push_event_delete_list();
        void push_types();
        void push_objects();
        void push_proposition_instance(std::string name);

        void push_pop_formula(std::string type);
        void push_formula(std::string type);
        void pop_formula();
        void pop_formula(const std::string& input);

        void set_object_type(std::string type);
        void set_state_reflexivity(bool val);
        bool is_state_reflexive();

        Atom_Id get_owner_input_index(const std::string& type, const std::string& name) const;
    private:
        std::tuple<Formula_Types, std::vector<Formula_Id>> pop_formula_info();
        Proposition convert_instance_to_proposition(const Proposition_Instance& proposition_instance);

        std::unordered_set<std::string> types;
        std::unordered_set<std::string> variable_list;
        std::vector<std::string> ordered_variable_list;
        std::vector<std::string> agents;
        std::vector<std::pair<std::string, std::string>> inputs;
        std::unordered_map<std::string, std::unordered_set<std::string>> objects;
        std::string current_object_type;
        std::vector<Proposition> propositions;
        std::vector<Proposition_Instance> proposition_instances;
        bool state_reflexivity;
        bool action_reflexivity;
        std::vector<std::string> seen_perceivability;
        std::vector<std::tuple<std::string, std::string, Formula>> edge_conditions;
        std::vector<std::unordered_set<std::string>> relations;

        std::map<Proposition_Instance, Proposition> instance_to_proposition;

        // Formula stuff
        Formula formula;
        std::vector<std::vector<Formula_Id>> formula_buffer;
        std::vector<Formula_Types> formula_buffer_type;
        std::unordered_map<std::string, Atom_Id> atom_to_id;



        // Event stuff
        std::string event_name;
        std::vector<Proposition> event_add_list;
        std::vector<Proposition> event_delete_list;
        std::vector<std::string> designated_events;
    };
}
