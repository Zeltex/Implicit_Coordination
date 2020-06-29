#include "Domain.hpp"

namespace del {

	void Domain::perform_do(const Agent_Id agent, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list) {

		std::vector<Proposition_Instance> add_set;
		for (auto proposition : add_list) {
			add_set.push_back(proposition);
		}

		std::vector<Proposition_Instance> delete_set;
		for (auto proposition : delete_list) {
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

	void Domain::perform_action(Action action) {
		const State& current_state = states.back();
		states.push_back(perform_product_update(current_state, action, agents));
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
	const Agent& Domain::get_agent(std::string name) const {
		for (auto& entry : agents) {
			if (entry.get_name() == name) {
				return entry;
			}
		}
		// TODO - Handle this
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
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

	void Domain::remove_observability(const std::vector<std::string>& observers, const std::vector<std::string>& observees) {
		for (auto& observer : observers) {
			Agent_Id observer_agent = get_agent_id(observer);
			std::vector<Agent_Id> observee_agents;
			for (auto& observee : observees) {
				observee_agents.push_back(get_agent_id(observee));
			}
			states.back().remove_observability(observer_agent, observee_agents);
		}
	}

	void Domain::add_observability(const std::vector<std::string>& observers, const std::vector<std::string>& observees) {
		for (auto& observer : observers) {
			Agent_Id observer_agent = get_agent_id(observer);
			std::vector<Agent_Id> observee_agents;
			for (auto& observee : observees) {
				observee_agents.push_back(get_agent_id(observee));
			}
			states.back().add_observability(observer_agent, observee_agents);
		}
	}

	void Domain::remove_perceivability(const std::vector<std::string>& perceivers, const std::vector<std::string>& perceivees) {
		for (auto& perceiver : perceivers) {
			Agent_Id perceiver_agent = get_agent_id(perceiver);
			std::vector<Agent_Id> perceivee_agents;
			for (auto& perceivee : perceivees) {
				perceivee_agents.push_back(get_agent_id(perceivee));
			}
			states.back().remove_perceivability(perceiver_agent, perceivee_agents);
		}
	}

	void Domain::add_perceivability(const std::vector<std::string>& perceivers, const std::vector<std::string>& perceivees) {
		for (auto& perceiver : perceivers) {
			Agent_Id perceiver_agent = get_agent_id(perceiver);
			std::vector<Agent_Id> perceivee_agents;
			for (auto& perceivee : perceivees) {
				perceivee_agents.push_back(get_agent_id(perceivee));
			}
			states.back().add_perceivability(perceiver_agent, perceivee_agents);
		}
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