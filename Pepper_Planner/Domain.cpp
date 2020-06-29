#include "Domain.hpp"

namespace del {

	void Domain::perform_do(const Agent_Id agent, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list) {

		std::vector<Proposition_Instance> add_set;
		for (const auto& proposition : add_list) {
			add_set.push_back(proposition);
		}

		std::vector<Proposition_Instance> delete_set;
		for (const auto& proposition : delete_list) {
			delete_set.push_back(proposition);
		}

		Formula f;
		f.f_top();
		Event_Id id = { 0 };
		Action_Event event = Action_Event(id, std::move(f), add_set, delete_set);


		Action action(agent, amount_of_agents);
		action.add_event(event);

		const State& current_state = states.back();
		states.push_back(perform_product_update(current_state, action, agents));

	}
	
	void Domain::perform_oc(const Agent_Id owner, std::vector<Proposition_Instance>&& add_list, std::vector<Proposition_Instance>&& delete_list, std::string perceivability_proposition, std::string observability_proposition) {
		std::unordered_set<size_t> obs;

		Action action(owner, amount_of_agents);
		action.add_event("oc", {0}, {}, std::move(add_list), std::move(delete_list));
		action.add_event("nothign", {1}, {}, {}, {});
		action.add_designated_event({ 0 });

		for (auto& agent : agents) {
			Formula condition00;
			std::vector<Formula_Id> proposition_ids00;
			proposition_ids00.reserve(obs.size());
			if (std::find(obs.begin(), obs.end(), agent.get_id().id) == obs.end()) {
				condition00.f_top();
			} else {
				Formula condition01;
				std::vector<Formula_Id> proposition_ids01;
				proposition_ids01.reserve(obs.size());
				for (auto& obs_id : obs) {
					auto obs_name = get_agent(Agent_Id{ obs_id }).get_name();
					proposition_ids00.push_back(condition00.f_prop({ perceivability_proposition, { agent.get_name(), obs_name} }));
					proposition_ids01.push_back(condition01.f_not(condition01.f_prop({ perceivability_proposition, { agent.get_name(), obs_name } })));
				}
				condition00.f_or(proposition_ids00);
				condition01.f_and(proposition_ids01);
				action.add_reachability(agent.get_id(), { 0 }, { 1 }, std::move(condition01));
			}
			action.add_reachability(agent.get_id(), { 0 }, { 0 }, std::move(condition00));
			action.add_reachability(agent.get_id(), { 1 }, { 1 }, {});

		}

		perform_action(action);
	}

	std::unordered_set<size_t> Domain::get_obs_set(const Agent_Id& owner, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list) {
		std::unordered_set<size_t> obs;
		auto owner_name = get_agent(owner).get_name();
		bool owner_found = false;
		for (auto proposition : add_list) {
			if (!owner_found && proposition.arguments.at(0) == owner_name) {
				owner_found = true;
			}
			obs.insert(get_agent(proposition.arguments.at(0)).get_id().id);
		}
		for (auto proposition : delete_list) {
			if (!owner_found && proposition.arguments.at(0) == owner_name) {
				owner_found = true;
			}
			obs.insert(get_agent(proposition.arguments.at(0)).get_id().id);
		}

		if (!owner_found) {
			obs.insert(get_agent(owner).get_id().id);
		}
		return std::move(obs);
	}

	void Domain::perform_action(Action action) {
		const State& current_state = states.back();
		states.push_back(perform_product_update(current_state, action, agents));
#ifdef DEBUG_PRINT
		std::string path;
#ifdef DEBUG_PRINT_PATH
		path = DEBUG_PRINT_PATH;
#else
		path = "../Debug_Output/";
#endif
		std::ofstream action_file;
		action_file.open(path + "dot/Action" + std::to_string(debug_counter++) + ".dot");
		action_file << "digraph G {\n" << action.to_graph(get_agents(), "a") << "}";
		action_file.close();
		std::ofstream state_file;
		state_file.open(path + "dot/State" + std::to_string(debug_counter) + ".dot");
		state_file << "digraph {subgraph cluster_0 {" << get_current_state().to_graph(get_agents(), "s0") << "}}";
		state_file.close();
#endif
	}

	State Domain::get_current_state() const {
		return states.back();
	}

	void Domain::set_name(const std::string name) {
		this->name = name;
	}

	std::string Domain::get_name() const {
		return name;
	}
	void Domain::set_amount_of_agents(size_t amount_of_agents) {
		this->amount_of_agents = amount_of_agents;
	}

	const std::vector<Agent>& Domain::get_agents() const {
		return agents;
	}

	// TODO - Optimise
	const Agent& Domain::get_agent(const std::string& name) const {
		for (auto& entry : agents) {
			if (entry.get_name() == name) {
				return entry;
			}
		}
		// TODO - Handle this
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
	}

	const Agent& Domain::get_agent(const Agent_Id& id) const {
		if (id.id > agents.size()) {
		// TODO - Handle this
			std::cerr << "No agent with name: " << name << "\n";
			exit(-1);
		} else {
			return agents[id.id];
		}
	}

	// TODO - Optimise
	Agent_Id Domain::get_agent_id(std::string name) const {
		for (auto& entry : agents) {
			if (entry.get_name() == name) {
				return entry.get_id();
			}
		}
		// TODO - Handle this
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
	}

	Agent_Id Domain::create_agent(std::string name) {
		Agent_Id id = Agent_Id{ agents.size() };
		agents.emplace_back(id, name);
		return id;
	}

	void Domain::set_atom_types(std::unordered_set<std::string> types) {
		atom_types = types;
	}

	const std::unordered_set<std::string>& Domain::get_atom_types() const {
		return atom_types;
	}

	const std::unordered_set<std::string>& Domain::get_all_atoms_of_type(std::string type) const {
		if (objects.find(type) == objects.end()) {
			std::cerr << "No objects of type: " << type << "\n";
			throw;
		}
		return objects.at(type);
	}

	void Domain::set_objects(std::unordered_map<std::string, std::unordered_set<std::string>> objects) {
		this->objects = objects;
	}

	void Domain::set_initial_state(State&& state) {
		states = {};
		states.push_back(state);
	}
}