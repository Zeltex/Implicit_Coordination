#include "Domain_Interface_Implementation.h"

namespace del {
	void Domain_Interface_Implementation::new_domain(std::string name) {
		std::cout << "Starting domain" << std::endl;
		domain.set_name(name);
	}

	void Domain_Interface_Implementation::finish_domain() {
		std::cout << "Finishing domain" << std::endl;
	}

	void Domain_Interface_Implementation::finish_problem() {
		std::cout << "Finishing problem" << std::endl;

		// Action reachability and reflexivity
		for (auto& action : actions) {
			action.set_amount_of_agents(domain.get_agents().size());

			// TODO - Removed option for implicit action reflexivity, should probably delete soon
			//if (action_reflexivity) {
			//	for (auto& agent : domain.get_agents()) {
			//		for (auto& event : action.get_events()) {
			//			action.add_reachability_relation(agent.get_id(), event.get_id(), event.get_id());
			//		}
			//	}
			//}
		}

		// Perceivability
		for (auto& perceiver_list : perceivability) {
			std::vector<Agent_Id> temp;
			for (auto& agent : perceiver_list.second) {
				temp.emplace_back(domain.get_agent_id(agent));
			}
			initial_state.add_perceivability(domain.get_agent_id(perceiver_list.first), temp);
		}

		// Observability
		for (auto& observer_list : observability) {
			std::vector<Agent_Id> temp;
			for (auto& agent : observer_list.second) {
				temp.emplace_back(domain.get_agent_id(agent));
			}
			initial_state.add_observability(domain.get_agent_id(observer_list.first), temp);
		}

		for (auto& action : actions) {
			library.add_general_action(action, domain);
		}
		auto temp = std::move(initial_state);
		initial_state = {};
		domain.set_initial_state(std::move(temp));
	}

	void Domain_Interface_Implementation::new_action(std::string name) {
		current_action = General_Action();
		current_action.set_name(name);
	}

	void Domain_Interface_Implementation::finish_action() {
		std::cout << "Finishing action" << std::endl;
		actions.push_back(std::move(current_action));
		current_action = {};
	}


	void Domain_Interface_Implementation::set_action_cost(size_t cost) {
		current_action.set_cost(cost);
	}

	void Domain_Interface_Implementation::set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) {
		current_action.set_action_input(std::move(inputs));
	}

	void Domain_Interface_Implementation::set_action_owner(std::string type, std::string name, Atom_Id id) {
		std::cout << "Action owner " << type << " " << name << std::endl;
		current_action.set_owner(type, id);
	}

	void Domain_Interface_Implementation::create_event(std::string name, Formula&& preconditions, std::vector<Proposition_Instance> add_list, std::vector<Proposition_Instance> delete_list) {
		current_action.create_event(name, std::move(preconditions), add_list, delete_list);
	}


	void Domain_Interface_Implementation::set_designated_events(std::vector<std::string> designated_events) {
		current_action.set_designated_events(designated_events);
	}

	void Domain_Interface_Implementation::set_types(const std::unordered_set<std::string>& types) {
		domain.set_atom_types(types);
	}

	void Domain_Interface_Implementation::add_proposition(std::string name, const std::vector<std::pair<std::string, std::string>>& inputs) {
		propositions.emplace_back(name, inputs);
	}

	void Domain_Interface_Implementation::set_objects(std::unordered_map<std::string, std::unordered_set<std::string>>&& objects) {
		size_t amount_of_agents = objects["agent"].size();
		initial_state.set_amount_of_agents(amount_of_agents);
		library.set_amount_of_agents(amount_of_agents);

		domain.set_objects(objects);
		for (auto entry : objects["agent"]) {
			domain.create_agent(entry);
		}
	}

	void Domain_Interface_Implementation::set_domain(std::string domain_name) {
		// TODO - problem using domain: domain_name
	}

	void Domain_Interface_Implementation::set_initial_propositions(const std::vector<Proposition_Instance>& propositions) {
		this->initial_propositions = propositions;
	}

	void Domain_Interface_Implementation::create_world(std::string name, const std::vector<Proposition_Instance>& propositions, const std::unordered_map<std::string, Atom_Id>& atom_to_id) {
		auto& world = initial_state.create_world();

		std::unordered_map<size_t, Atom_Id> converter;
		converter.reserve(atom_to_id.size());
		for (auto& entry : atom_to_id) {
			converter[entry.second.id] = domain.get_atom_id(entry.first);
		}

		std::vector<Proposition_Instance> result;
		result.reserve(propositions.size());
		for (auto& proposition : propositions) {
			result.emplace_back(proposition, converter);
		}


		world.add_true_propositions(result);
		world_name_to_id[name] = world.get_id();
	}

	void Domain_Interface_Implementation::set_designated_worlds(const std::unordered_set<std::string>& designated_worlds) {
		for (auto& entry : designated_worlds) {
			initial_state.add_designated_world(world_name_to_id[entry]);
		}
	}

	void Domain_Interface_Implementation::create_action_reflexive_reachables() {
		action_reflexivity = true;
	}
	
	void Domain_Interface_Implementation::create_state_reflexive_reachables() {
		for (auto& world : initial_state.get_worlds()) {
			for (auto& agent : domain.get_agents()) {
				initial_state.add_indistinguishability_relation(agent.get_id(), world.get_id(), world.get_id());
			}
		}
	}

	void Domain_Interface_Implementation::add_reachability(std::string name, const std::vector<std::pair<std::string, std::string>>& reachables) {
		for (auto& entry : reachables) {
			initial_state.add_indistinguishability_relation(domain.get_agent_id(name), world_name_to_id[entry.first], world_name_to_id[entry.second]);
		}
	}

	std::tuple<Domain, Action_Library, Formula> Domain_Interface_Implementation::get_loaded() {
		return { std::move(domain), std::move(library), std::move(goal) };
	}

	void Domain_Interface_Implementation::set_announce_enabled() {
		library.set_announce_enabled();
	}

	void Domain_Interface_Implementation::set_goal(Formula&& goal, const std::unordered_map<std::string, Atom_Id>& atom_to_id) {

		std::unordered_map<size_t, Atom_Id> atom_converter;
		std::unordered_map<size_t, size_t> agent_converter;
		atom_converter.reserve(atom_to_id.size());
		for (auto& entry : atom_to_id) {
			auto atom_id = domain.get_atom_id(entry.first);
			atom_converter[entry.second.id] = atom_id;
			auto agent = this->domain.get_agent_id_optional(atom_id);
			if (agent.has_value()) {
				agent_converter[atom_id.id] = agent.value().id;
			}
		}

		this->goal = Formula(goal, atom_converter, agent_converter);
	}

	void Domain_Interface_Implementation::add_edge_condition(Atom_Id agent, std::vector< std::tuple<std::string, std::string, Formula>>&& edge_conditions) {

		std::vector<Edge_Condition> temp;
		temp.reserve(edge_conditions.size());
		for (auto&[event_from, event_to, condition] : edge_conditions) {
			temp.emplace_back(std::move(event_from), std::move(event_to), std::move(condition));
		}
		current_action.add_edge_condition(agent, std::move(temp));
	}

	void Domain_Interface_Implementation::add_observability(std::string observer, const std::vector<std::string>& agents) {
		observability[observer] = agents;
	}
	
	void Domain_Interface_Implementation::add_perceivability(std::string perceiver, const std::vector<std::string>& agents) {
		perceivability[perceiver] = agents;
	}
}