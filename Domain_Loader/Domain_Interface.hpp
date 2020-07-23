#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>

#include "Formula.hpp"
#include "Formula_Component.hpp"
#include "Loader_Types.hpp"

namespace del {
    class Domain_Interface {
    public:
        virtual void new_action									(std::string name) = 0;
        virtual void new_domain									(std::string name) = 0;
        virtual void finish_action								() = 0;
        virtual void finish_domain								() = 0;
        virtual void finish_problem								() = 0;


        virtual void set_action_cost							(size_t cost) = 0;
        virtual void set_action_input							(std::vector<std::pair<std::string, std::string>> inputs) = 0;
        virtual void set_action_owner							(std::string type, std::string name) = 0;
        virtual void set_announce_enabled						() = 0;
        virtual void set_designated_events						(std::vector<std::string> designated_events) = 0;
        virtual void set_designated_worlds						(const std::unordered_set<std::string>& designated_worlds) = 0;
        virtual void set_domain									(std::string domain_name) = 0;
        virtual void set_goal									(del::Formula&& goal, const std::unordered_map<std::string, Atom_Id>& atom_to_id) = 0;
        virtual void set_initial_propositions					(const std::vector<Proposition_Instance>& propositions) = 0;
        virtual void set_objects								(std::unordered_map<std::string, std::unordered_set<std::string>>&& objects) = 0;
        virtual void set_types									(const std::unordered_set<std::string>& types) = 0;


        virtual void create_event								(std::string name, del::Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list) = 0;
        virtual void create_world								(std::string name, const std::vector<Proposition_Instance>& propositions, const std::unordered_map<std::string, Atom_Id>& atom_to_id) = 0;
        virtual void create_action_reflexive_reachables			() = 0;
        virtual void create_state_reflexive_reachables			() = 0;

        virtual void add_edge_condition							(std::string agent, std::vector< std::tuple<std::string, std::string, del::Formula>>&& edge_conditions) = 0;
        virtual void add_observability							(std::string observer, const std::vector<std::string>& agents) = 0;
        virtual void add_perceivability							(std::string perceiver, const std::vector<std::string>& agents) = 0;
        virtual void add_proposition							(std::string name, const std::vector<std::pair<std::string, std::string>>& inputs) = 0;
        virtual void add_reachability							(std::string name, const std::vector<std::pair<std::string, std::string>>& reachables) = 0;

    private:
        std::vector<std::string> buffer_list;
    };
}
