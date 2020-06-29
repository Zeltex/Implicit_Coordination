#pragma once

#include <vector>
#include <string>

#include "Types.hpp"
#include "State.hpp"
#include "Formula.hpp"
#include "Action_Event.hpp"
#include "Action.hpp"
#include "DEL_Operations.hpp"

namespace del {
	class Domain {
	public:

		Domain() : amount_of_agents(0), states(), name(""), agents(), atom_types() {}
		Domain(size_t amount_of_agents, State initial_state) : amount_of_agents(amount_of_agents), states({ initial_state }), name(), agents(), atom_types() {}

		void perform_do(const Agent_Id i, const std::vector<Proposition_Instance>& add, const std::vector<Proposition_Instance>& del);
		void perform_oc(const Agent_Id i, std::vector<Proposition_Instance>&& add_list, std::vector<Proposition_Instance>&& delete_list, std::string perceivability_proposition = "perceives", std::string observability_proposition = "obeserves");
		void perform_action(Action action);
		State get_current_state() const;
		void set_name(const std::string name);
		void set_amount_of_agents(size_t amount_of_agents);
		std::string get_name() const;

		const std::vector<Agent>& get_agents() const;
		const std::unordered_set<std::string>& get_atom_types() const;
		const std::unordered_set<std::string>& get_all_atoms_of_type(std::string type) const;
		Agent_Id get_agent_id(std::string name) const;
		const Agent& get_agent(const std::string& name) const;
		const Agent& get_agent(const Agent_Id& id) const;
		Agent_Id create_agent(std::string name);

		void set_atom_types(std::unordered_set<std::string> types);
		void set_objects(std::unordered_map<std::string, std::unordered_set<std::string>> objects);
		void set_initial_state(State&& state);
	private:
		std::unordered_set<size_t> get_obs_set(const Agent_Id& owner, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list);

		size_t amount_of_agents;
		std::vector<State> states;
		std::string name;
		std::vector<Agent> agents;
		std::unordered_set<std::string> atom_types;
		std::unordered_map<std::string, std::unordered_set<std::string>> objects;
#ifdef DEBUG_PRINT
		size_t debug_counter = 0;
#endif
	};
}