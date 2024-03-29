#include "World.hpp"

#include "Action_Events.hpp"
#include "Atom_Lookup.hpp"
#include "Domain.hpp"
#include "General_World.hpp"
#include "Propositions_Lookup.hpp"

namespace del {


	World::World(const General_World& other, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup)
		: id(other.world_id),
		true_propositions()
	{
		for (const General_Proposition_Instance& proposition_instance : other.propositions)
		{
			true_propositions.insert(propositions_lookup.get(proposition_instance, atom_lookup));
		}
	}

	World::World(const World& other, const Action_Event& action, const World_Id& id)
		: id(id)
	{
		true_propositions = other.get_true_propositions();
		true_propositions.remove(action.get_delete_list());
		true_propositions.insert(action.get_add_list());
	}

	World_Id World::get_id() const {
		return id;
	}

	World World::create_copy(World_Id id) const {
		return World(id, true_propositions);
	}

	void World::add_true_propositions(const Propositions& propositions) {
		true_propositions.insert(propositions);
	}

	void World::remove_true_propositions(const Propositions& propositions) {
		true_propositions.remove(propositions);
	}

	const Propositions& World::get_true_propositions() const {
		return true_propositions;
	}

	std::string World::to_string() const{
		return "World " + std::to_string(id.id) + ": " + true_propositions.to_string();
	}

	void World::set_id(World_Id id) {
		this->id = std::move(id);
	}

	bool World::operator!=(const World& other) const 
	{
		return true_propositions != other.true_propositions;
	}

	std::string World::to_hash() const {
		return true_propositions.to_hash();
	}
}