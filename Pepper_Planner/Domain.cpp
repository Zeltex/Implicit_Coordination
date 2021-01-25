#include "Domain.hpp"
#include "Core.hpp"

namespace del {

	//void Domain::perform_do(const Agent_Id agent, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list) {

	//	std::vector<Proposition_Instance> add_set;
	//	for (const auto& proposition : add_list) {
	//		add_set.push_back(proposition);
	//	}

	//	std::vector<Proposition_Instance> delete_set;
	//	for (const auto& proposition : delete_list) {
	//		delete_set.push_back(proposition);
	//	}

	//	Formula f;
	//	f.f_top();
	//	Event_Id id = { 0 };
	//	Action_Event event = Action_Event(id, std::move(f), add_set, delete_set);


	//	Action action(agent, amount_of_agents);
	//	action.add_event(event);

	//	const State& current_state = states.back();
	//	states.push_back(perform_product_update(current_state, action, agents, *this));

	//}
	//
	//void Domain::perform_oc(const Agent_Id owner, std::vector<Proposition_Instance>&& add_list, std::vector<Proposition_Instance>&& delete_list, std::string perceivability_proposition, std::string observability_proposition) {
	//	std::unordered_set<size_t> obs;


	//	Action action(owner, amount_of_agents);
	//	action.add_event("oc", {0}, {}, std::move(add_list), std::move(delete_list));
	//	action.add_event("nothing", {1}, {}, {}, {});
	//	action.add_designated_event({ 0 });

	//	for (auto& agent : agents) {
	//		Atom_Id agent_atom_id = get_atom_id(agent.get_name());

	//		Formula condition00;
	//		std::vector<Formula_Id> proposition_ids00;
	//		proposition_ids00.reserve(obs.size());
	//		if (std::find(obs.begin(), obs.end(), agent.get_id().id) == obs.end()) {
	//			condition00.f_top();
	//		} else {
	//			Formula condition01;
	//			std::vector<Formula_Id> proposition_ids01;
	//			proposition_ids01.reserve(obs.size());
	//			for (auto& obs_id : obs) {
	//				auto obs_atom_id = get_atom_id(get_agent(Agent_Id{ obs_id }).get_name());
	//				proposition_ids00.push_back(condition00.f_prop({ perceivability_proposition, { agent_atom_id, obs_atom_id} }));
	//				proposition_ids01.push_back(condition01.f_not(condition01.f_prop({ perceivability_proposition, { agent_atom_id, obs_atom_id} })));
	//			}
	//			condition00.f_or(proposition_ids00);
	//			condition01.f_and(proposition_ids01);
	//			action.add_reachability(agent.get_id(), { 0 }, { 1 }, std::move(condition01));
	//		}
	//		action.add_reachability(agent.get_id(), { 0 }, { 0 }, std::move(condition00));
	//		action.add_reachability(agent.get_id(), { 1 }, { 1 }, {});

	//	}

	//	perform_action(action);
	//}

	//std::unordered_set<size_t> Domain::get_obs_set(const Agent_Id& owner, const std::vector<Proposition_Instance>& add_list, const std::vector<Proposition_Instance>& delete_list) {
	//	std::unordered_set<size_t> obs;
	//	auto owner_name = get_agent(owner).get_name();
	//	auto owner_atom_id = get_atom_id(owner_name);

	//	bool owner_found = false;
	//	for (auto proposition : add_list) {
	//		if (!owner_found && proposition.arguments.at(0) == owner_atom_id) {
	//			owner_found = true;
	//		}
	//		obs.insert(get_agent_from_atom(proposition.arguments.at(0)).get_id().id);
	//	}
	//	for (auto proposition : delete_list) {
	//		if (!owner_found && proposition.arguments.at(0) == owner_atom_id) {
	//			owner_found = true;
	//		}
	//		obs.insert(get_agent_from_atom(proposition.arguments.at(0)).get_id().id);
	//	}

	//	if (!owner_found) {
	//		obs.insert(get_agent(owner).get_id().id);
	//	}
	//	return std::move(obs);
	//}

	void Domain::perform_action(Action action) {
		const State& current_state = states.back();
		auto product_update = perform_product_update(current_state, action, agents, *this);
#if BISIM_CONTRACTION_ENABLED == 1
		product_update = perform_k_bisimilar_contraction(std::move(product_update), BISIMILAR_DEPTH);
#endif
		states.push_back(std::move(product_update));
		PRINT_ACTION_TO_CONSOLE(action, *(this));
		PRINT_ACTION(action, *(this), debug_counter++);
		PRINT_STATE(get_current_state(), *(this), debug_counter);
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
			std::cerr << "No agent with id: " << id.id << "\n";
			exit(-1);
		} else {
			return agents[id.id];
		}
	}

	const Agent& Domain::get_agent_from_atom(const Atom_Id& id) const {
		return get_agent(get_atom_name(id));
	}

	std::optional<Agent_Id> Domain::get_agent_id_optional(Atom_Id atom_id) const {
		auto it = atom_to_agent.find(atom_id.id);
		if (it != atom_to_agent.end()) {
			return { it->second };
		}
		return {};
	}

	// TODO - Optimise
	Agent_Id Domain::get_agent_id(const std::string& name) const {
		for (auto& entry : agents) {
			if (entry.get_name() == name) {
				return entry.get_id();
			}
		}
		// TODO - Handle this
		std::cerr << "No agent with name: " << name << "\n";
		exit(-1);
	}

	Agent_Id Domain::get_agent_id(Atom_Id atom_id) const {
		auto name = get_atom_name(atom_id);
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
		Agent_Id agent_id = Agent_Id{ agents.size() };
		Atom_Id atom_id = get_atom_id(name);
		agents.push_back(Agent(agent_id, atom_id, name));
		atom_to_agent[atom_id.id] = agent_id;
		amount_of_agents = agents.size();
		return agent_id;
	}

	void Domain::set_atom_types(std::unordered_set<std::string> types) {
		atom_types = types;
	}

	const std::unordered_set<std::string>& Domain::get_atom_types() const {
		return atom_types;
	}

	const std::vector<Atom_Id>& Domain::get_all_atoms_of_type(const std::string& type) const {
		if (objects.find(type) == objects.end()) {
			std::cerr << "No objects of type: " << type << "\n";
			exit(-1);
		}
		return objects.at(type);
	}

	void Domain::set_objects(const std::unordered_map<std::string, std::unordered_set<std::string>>& objects, const std::unordered_map<std::string, Atom_Id>& atom_to_id) {
		this->objects.clear();
		this->objects.reserve(objects.size());
		this->atom_to_id = atom_to_id;
		this->id_to_atom = {};

		for (auto& [atom, id] : atom_to_id) {
			id_to_atom.insert(std::pair(id.id, atom));
		}

		// Recording all atoms of types
		for (auto& type : objects) {
			this->objects[type.first].reserve(type.second.size());
			for (auto& atom : type.second) {
				this->objects[type.first].push_back(atom_to_id.at(atom).id);
			}
		}
	}

	void Domain::set_initial_state(State&& state) {
		states = {};
		states.push_back(state);
	}


	std::string Domain::get_atom_name(Atom_Id atom_id) const {
		return id_to_atom.at(atom_id.id);
	}

	Atom_Id Domain::get_atom_id(const std::string& atom_name) const {
		return atom_to_id.at(atom_name);
	}

	const std::unordered_map<size_t, std::string>& Domain::get_id_to_atom() const {
		return id_to_atom;
	}

	const std::unordered_map<std::string, Atom_Id>& Domain::get_atom_to_id() const {
		return atom_to_id;
	}
	
	std::unordered_map<std::string, size_t> Domain::get_agent_to_id() const {
		std::unordered_map<std::string, size_t> result;
		for (auto& agent : agents) {
			result[agent.get_name()] = agent.get_id().id;
		}
		return result;
	}

	void Domain::set_rigid_atoms(std::vector<Proposition> rigid_atoms) {
		this->rigid_atoms = std::move(rigid_atoms);
	}

	const std::vector<Proposition> Domain::get_atom_rigids() const {
		return rigid_atoms;
	}

	void Domain::set_proposition_instances(std::map<Proposition_Instance, Proposition>&& instance_to_proposition) {
		proposition_to_instance.clear();
		for (const auto& [prop_instance, prop] : instance_to_proposition) {
			proposition_to_instance[prop] = prop_instance;
		}
		this->instance_to_proposition = std::move(instance_to_proposition);
	}

	const Proposition& Domain::get_proposition(const Proposition_Instance& proposition_instance) const {
		return instance_to_proposition.at(proposition_instance);
	}

	const Proposition_Instance& Domain::get_proposition_instance(const Proposition& proposition) const {
		return proposition_to_instance.at(proposition);
	}

	size_t Domain::get_amount_of_agents() const {
		return amount_of_agents;
	}


}