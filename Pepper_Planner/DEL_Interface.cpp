#include "DEL_Interface.hpp"

namespace del {

	DEL_Interface::DEL_Interface(size_t domain_to_load) : domain(), planner(), has_policy(false), policy(false), action_library(), pepper_id({ 0 }) {
		Environment_Loader environment_loader;
		auto [domain, action_library, goal] = environment_loader.load(domain_to_load);
		this->domain = domain;
		this->action_library = std::move(action_library);
		this->goal = std::move(goal);
	}
	
	DEL_Interface::DEL_Interface(State initial_state, Action_Library library) : 
			domain(initial_state.get_number_of_agents(), initial_state), has_policy(false), policy(false), action_library(), pepper_id({ 0 }) {
		domain = Domain(initial_state.get_number_of_agents(), initial_state);
		action_library = std::move(library);
	}

	DEL_Interface::DEL_Interface(std::string file_path) :
		domain(), has_policy(false), policy(false), action_library(), pepper_id({ 0 }) {
		Loader loader;
		Domain_Interface_Implementation domain_interface;
		loader.parse(&domain_interface, file_path);

		auto [domain, library, goal] = domain_interface.get_loaded();
		this->domain = std::move(domain);
		this->action_library = std::move(library);
		this->goal = std::move(goal);

#ifdef DEBUG_PRINT
		std::string path;
#ifdef DEBUG_PRINT_PATH
		path = DEBUG_PRINT_PATH;
#else
		path = "../Debug_Output/";
#endif
		std::string command = "rm -r " + path + "dot/*";
		system(command.c_str());
		command = "rm -r " + path + "png/*";
		system(command.c_str());
		std::ofstream state_file;
		state_file.open(path + "dot/State0.dot");
		state_file << "digraph {subgraph cluster_0 {" << this->domain.get_current_state().to_graph(this->domain.get_agents(), "s0", this->domain) << "}}";
		state_file.close();
#endif

	}
	
	Interface_DTO DEL_Interface::get_next_action() {
		if (has_policy) {
			auto [action, solved] = policy.get_action(domain.get_current_state());
			if (solved) {
				std::string announce_string = "";
				if (action.get_owner() == pepper_id) {
					auto& events = action.get_events();
					if (events.size() > 0) {
						announce_string = events[0].get_preconditions().to_string(domain.get_id_to_atom());
					}
				}
				return Interface_DTO(action, announce_string);
			}
		} else {
			return Interface_DTO();
		}
	}
	
	void DEL_Interface::perform_do(const Agent_Id i, const std::vector<Proposition_Instance>& add, const std::vector<Proposition_Instance>& del) {
		domain.perform_do(i, add, del);
	}

	void DEL_Interface::perform_oc(const Agent_Id i, std::vector<std::vector<std::string>>&& add, std::vector<std::vector<std::string>>&& del) {
		std::vector<Proposition_Instance> add_list;
		add_list.reserve(add.size());
		for (auto& entry : add) {
			if (entry.size() < 1) continue;
			std::vector<Atom_Id> temp_atoms;
			bool first = true;

			for (auto& atom : entry) {
				if (first) {
					first = false;
				} else {
					temp_atoms.emplace_back(domain.get_atom_id(atom));
				}
			}

			add_list.emplace_back(entry[0], temp_atoms);
		}

		std::vector<Proposition_Instance> del_list;
		del_list.reserve(del.size());
		for (auto& entry : del) {
			if (entry.size() < 1) continue;
			std::vector<Atom_Id> temp_atoms;
			bool first = true;

			for (auto& atom : entry) {
				if (first) {
					first = false;
				} else {
					temp_atoms.emplace_back(domain.get_atom_id(atom));
				}
			}
			del_list.emplace_back(entry[0], temp_atoms);
		}

		domain.perform_oc(i, std::move(add_list), std::move(del_list));
	}

	void DEL_Interface::perform_oc(const std::string owner_name, std::vector<std::vector<std::string>>&& add, std::vector<std::vector<std::string>>&& del) {

		return perform_oc(domain.get_agent(owner_name).get_id(), std::move(add), std::move(del));
	}
	
	void DEL_Interface::perform_action(Action action) {
		domain.perform_action(action);
	}

	void DEL_Interface::perform_action(const std::string& name, const std::string& owner, const std::vector<std::string>& arguments) {
		std::vector<Atom_Id> temp_arguments;
		temp_arguments.reserve(arguments.size());
		for (auto& argument : arguments) {
			temp_arguments.push_back(domain.get_atom_id(argument));
		}


		auto action = action_library.get_general_action(name).create_action(domain.get_atom_id(owner), std::move(temp_arguments), domain);
		domain.perform_action(action);

	}
	
	bool DEL_Interface::create_policy(Formula goal) {
		this->goal = std::move(goal);
		return create_policy();
	}

	bool DEL_Interface::create_policy() {
		policy = planner.find_policy(this->goal, action_library, domain.get_current_state(), domain.get_agents(), domain);

#ifdef DEBUG_PRINT
		std::string path;
#ifdef DEBUG_PRINT_PATH
		path = DEBUG_PRINT_PATH;
#else
		path = "../Debug_Output/";
#endif
		std::ofstream state_file;
		state_file.open(path + "Policy.dot");
		state_file << "digraph {\ncompound = true;\n" << policy.to_graph(domain.get_agents(), domain) << "}";
		state_file.close();
#endif

		has_policy = policy.is_solved();
		return policy.is_solved();
	}

	bool DEL_Interface::is_solved() {
		return domain.get_current_state().valuate(goal);
	}
}