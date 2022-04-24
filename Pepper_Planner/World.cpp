#include "World.hpp"
#include "Domain.hpp"
#include "Action_Events.hpp"

namespace del {

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
		return World(id, true_propositions.data);
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

	std::string World::to_string(const Domain& domain) const{
		std::string result = "World " + std::to_string(id.id) + ": ";
		bool first = true;
		for (const Proposition& proposition : true_propositions.data) {
			if (first) {
				first = false;
			}
			else {
				result += ";";
			}
			result += domain.get_proposition_instance(proposition).to_string(domain.get_id_to_atom());
		}
		return result;
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