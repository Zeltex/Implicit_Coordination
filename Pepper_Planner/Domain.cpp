#include "Domain.hpp"
#include "Core.hpp"

namespace del 
{

	void Domain::add_new_current_state(const State& state) 
	{
		states.push_back(state);
	}

	State Domain::get_current_state() const {
		return states.back();
	}

	const Agents& Domain::get_agents() const {
		return agents;
	}

	const Agent& Domain::get_agent(const std::string& name) const {
		return agents.get(name);
	}

	const Agent& Domain::get_agent(const Agent_Id& id) const {
		return agents.get(id);
	}

	Domain::Domain(General_Domain general_domain)
		: agents(general_domain.agents)
	{
		// TODO
		throw;
	}

	const Agent& Domain::get_agent(const Atom_Id& id) const {
		return get_agent(get_atom(id).get_name());
	}

	const Atoms& Domain::get_all_atoms_of_type(const std::string& type) const {
		if (objects.find(type) == objects.end()) {
			std::cerr << "No objects of type: " << type << "\n";
			exit(-1);
		}
		return objects.at(type);
	}

	// TODO - Should be parsed in constructor
	void Domain::set_objects(const std::unordered_map<std::string, std::unordered_set<std::string>>& objects, const std::unordered_map<std::string, Atom>& name_to_atom) {
		this->objects.clear();
		this->objects.reserve(objects.size());
		this->name_to_atom = name_to_atom;
		this->id_to_atom = {};

		for (auto& [name, atom] : name_to_atom) {
			id_to_atom.insert(std::pair(atom.get_id().id, atom));
		}

		// Recording all atoms of types
		for (auto& type : objects) {
			this->objects[type.first].reserve(type.second.size());
			for (auto& atom : type.second) {
				this->objects[type.first].insert(name_to_atom.at(atom));
			}
		}
	}

	const Atom& Domain::get_atom(const Atom_Id& atom_id) const {
		return id_to_atom.at(atom_id.id);
	}

	const Atom& Domain::get_atom(const std::string& atom_name) const {
		return name_to_atom.at(atom_name);
	}

	void Domain::set_rigid_atoms(const Propositions& rigid_atoms) {
		this->rigid_atoms = rigid_atoms;
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

	bool Domain::is_rigid(const Proposition& proposition) const
	{
		return rigid_atoms.contains(proposition);
	}
}