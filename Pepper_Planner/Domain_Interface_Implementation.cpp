//#include "Domain_Interface_Implementation.hpp"
//
//#include "Edge_Conditions.hpp"
//#include "General_Domain.hpp"
//
//namespace del {
//	void Domain_Interface_Implementation::new_domain(std::string name) {
//
//	}
//
//	void Domain_Interface_Implementation::finish_domain() {
//	}
//
//	void Domain_Interface_Implementation::finish_problem(const General_Domain& general_domain) {
//
//		general_domain.get_atoms();
//
//		domain = new Domain(initial_state.to_state(), type_to_atom);
//		for (auto& action : actions) {
//			library.add_general_action(action, *domain);
//		}
//		initial_state = {};
//	}
//
//	void Domain_Interface_Implementation::new_action(std::string name) {
//		current_action = General_Action();
//		current_action.set_name(name);
//	}
//
//	void Domain_Interface_Implementation::finish_action(std::map<Proposition_Instance, Proposition> instance_to_proposition) {
//		current_action.set_instance_to_proposition(instance_to_proposition);
//		actions.push_back(std::move(current_action));
//		current_action = {};
//	}
//
//
//	void Domain_Interface_Implementation::set_action_cost(size_t cost) {
//		current_action.set_cost(cost);
//	}
//
//	void Domain_Interface_Implementation::set_action_input(std::vector<std::pair<std::string, std::string>>&& inputs) {
//		current_action.set_action_input(std::move(inputs));
//	}
//
//	void Domain_Interface_Implementation::set_action_owner(std::string type, std::string name, Atom_Id id) {
//		//current_action.set_owner(type, id);
//	}
//
//	void Domain_Interface_Implementation::create_event(std::string name, Formula&& preconditions, std::vector<Proposition> add_list, std::vector<Proposition> delete_list) {
//		current_action.create_event(name, std::move(preconditions), add_list, delete_list);
//	}
//
//
//	void Domain_Interface_Implementation::set_designated_events(std::vector<std::string> designated_events) {
//		current_action.set_designated_events(designated_events);
//	}
//
//	void Domain_Interface_Implementation::set_types(const std::unordered_set<std::string>& types) {
//		
//	}
//
//	void Domain_Interface_Implementation::add_proposition(std::string name, const std::vector<std::pair<std::string, std::string>>& inputs) {
//		general_propositions.emplace_back(name, inputs);
//	}
//
//	void Domain_Interface_Implementation::set_objects(std::unordered_map<std::string, std::unordered_set<std::string>>&& type_to_atom, const std::unordered_map<std::string, Atom_Id>& atom_to_id) {
//		size_t amount_of_agents = type_to_atom["agent"].size();
//		library.set_amount_of_agents(amount_of_agents);
//
//		domain.set_objects(type_to_atom, atom_to_id);
//		for (const auto& entry : type_to_atom["agent"]) {
//			domain.create_agent(entry);
//		}
//
//		std::map<Proposition_Instance, Proposition> instance_to_proposition;
//		for (const auto& general_proposition : general_propositions) {
//			const auto& inputs = general_proposition.inputs;
//			std::vector<size_t> indices(inputs.size());
//
//			// Check at least one atom of each input type exists
//			bool empty_input = false;
//			for (const auto& input : inputs) {
//				if (type_to_atom.at(input.first).empty()) {
//					empty_input = true;
//					break;
//				}
//			}
//			if (empty_input) continue;
//
//			// Convert object set to indicable list
//			std::vector<std::vector<std::string>> list_atoms;
//			for (const auto& input : inputs) {
//				list_atoms.emplace_back();
//				for (const auto& object : type_to_atom.at(input.first)) {
//					list_atoms.back().push_back(object);
//				}
//			}
//
//			// Produce all grounded propositions
//			bool done = false;
//			while (!done) {
//				Atoms grounded_input;
//				for (size_t i = 0; i < indices.size(); ++i) {
//					const std::string& input_type = inputs.at(i).first;
//					const std::string& atom = list_atoms.at(i).at(indices.at(i));
//					grounded_input.insert(domain.get_atom_id(atom));
//				}
//
//				instance_to_proposition.insert(std::pair(Proposition_Instance(general_proposition.name, grounded_input), instance_to_proposition.size()));
//	
//				// Advance indices
//				size_t index = 0;
//				while (!done && ++indices.at(index) >= list_atoms.at(index).size()) {
//					indices.at(index++) = 0;
//					done = index >= indices.size();
//				}				
//			}
//		}
//		domain.set_proposition_instances(std::move(instance_to_proposition));
//	}
//
//	void Domain_Interface_Implementation::set_domain(std::string domain_name) {
//		// TODO - problem using domain: domain_name
//	}
//
//	void Domain_Interface_Implementation::set_initial_propositions(const std::vector<Proposition_Instance>& proposition_instances) {
//		Propositions propositions;
//		propositions.reserve(proposition_instances.size());
//		for (const Proposition_Instance& proposition_instance : proposition_instances) {
//			propositions.insert(domain.get_proposition(proposition_instance));
//		}
//		domain.set_rigid_atoms(propositions);
//	}
//
//	void Domain_Interface_Implementation::create_world(std::string name, const std::vector<Proposition_Instance>& proposition_instances) {
//		auto& world = initial_state.create_world();
//		//auto converter = get_loader_to_planner_converter(atom_to_id);
//		//auto propositions = convert_loader_instances_to_planner_propositions(proposition_instances, converter);
//		std::vector<Proposition> propositions;
//		propositions.reserve(proposition_instances.size());
//		for (auto& proposition_instance : proposition_instances) {
//			propositions.push_back(domain.get_proposition(proposition_instance));
//		}
//
//		world.add_true_propositions(propositions);
//		world_name_to_id[name] = world.get_id();
//	}
//
//	void Domain_Interface_Implementation::set_designated_worlds(const std::unordered_set<std::string>& designated_worlds) {
//		for (auto& entry : designated_worlds) {
//			initial_state.set_world_designated(world_name_to_id[entry]);
//		}
//	}
//
//	void Domain_Interface_Implementation::create_action_reflexive_reachables() {
//		action_reflexivity = true;
//	}
//	
//	void Domain_Interface_Implementation::create_state_reflexive_reachables() {
//		for (auto& world : initial_state.get_worlds()) {
//			for (auto& agent : domain.get_agents()) {
//				initial_state.add_accessibility_relation(agent.get_id(), world.get_id(), world.get_id());
//			}
//		}
//	}
//
//	void Domain_Interface_Implementation::add_reachability(std::string name, const std::vector<std::pair<std::string, std::string>>& reachables) {
//		for (auto& entry : reachables) {
//			initial_state.add_accessibility_relation(domain.get_agent_id(name), world_name_to_id[entry.first], world_name_to_id[entry.second]);
//		}
//	}
//
//	std::tuple<Domain, Action_Library, Formula> Domain_Interface_Implementation::get_loaded() {
//		return { std::move(domain), std::move(library), std::move(goal) };
//	}
//
//	void Domain_Interface_Implementation::set_announce_enabled() {
//		library.set_announce_enabled();
//	}
//
//	void Domain_Interface_Implementation::set_goal(Formula&& goal, const std::map<Proposition_Instance, Proposition>& instance_to_proposition, const std::unordered_map<std::string, Atom_Id>& atom_to_id) {
//		auto converter = get_loader_to_formula_converter(instance_to_proposition);
//
//		this->goal = Formula(goal, converter);
//	}
//
//	void Domain_Interface_Implementation::add_edge_condition(Atom_Id agent, std::vector< std::tuple<std::string, std::string, Formula>>&& edge_conditions_input) {
//
//		General_Edge_Conditions edge_conditions;
//		for (auto&[event_from, event_to, condition] : edge_conditions_input) {
//			edge_conditions.insert({ std::move(event_from), std::move(event_to), std::move(condition) });
//		}
//		current_action.add_edge_condition(agent, std::move(edge_conditions));
//	}
//
//	void Domain_Interface_Implementation::add_observability(std::string observer, const std::vector<std::string>& agents) {
//		observability[observer] = agents;
//	}
//	
//	void Domain_Interface_Implementation::add_perceivability(std::string perceiver, const std::vector<std::string>& agents) {
//		perceivability[perceiver] = agents;
//	}
//
//	// Map from domain_loader ids to pepper_planner ids (using size_t and Atom_Id)
//	std::unordered_map<size_t, Atom_Id> Domain_Interface_Implementation::get_loader_to_planner_converter(const std::unordered_map<std::string, Atom_Id>& atom_to_id) const{
//		std::unordered_map<size_t, Atom_Id> converter;
//		converter.reserve(atom_to_id.size());
//		for (const auto& entry : atom_to_id) {
//			converter[entry.second.id] = domain.get_atom_id(entry.first);
//		}
//		return converter;
//	}
//
//	// Map from domain_loader ids to pepper_planner ids (using Proposition)
//	std::map<Proposition, Proposition> Domain_Interface_Implementation::get_loader_to_formula_converter(const std::map<Proposition_Instance, Proposition>& instance_to_proposition) const {
//		std::map<Proposition, Proposition> converter;
//		for (const auto& entry : instance_to_proposition) {
//			converter[entry.second] = domain.get_proposition(entry.first);
//		}
//		return converter;
//	}
//
//	std::vector<Proposition> Domain_Interface_Implementation::convert_loader_instances_to_planner_propositions(const std::vector<Proposition_Instance>& proposition_instances, const std::map<size_t, Atom_Id>& converter) const {
//		std::vector<Proposition> propositions;
//		propositions.reserve(proposition_instances.size());
//		for (const auto& proposition_instance : proposition_instances) {
//			auto converted_instance = Proposition_Instance(proposition_instance, converter);
//			auto& proposition = domain.get_proposition(converted_instance);
//			propositions.push_back(proposition);
//		}
//		return propositions;
//	}
//}