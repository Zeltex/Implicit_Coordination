#include "World.hpp"
#include "Domain.hpp"

namespace del {

	World_Id World::get_id() const {
		return id;
	}

	World World::create_copy(World_Id id) const {
		return World(id, true_propositions);
	}

	void World::add_true_propositions(const std::vector<Proposition_Instance> propositions) {
		for (auto proposition : propositions) {
			true_propositions.push_back(proposition);
		}
	}

	void World::remove_true_propositions(const std::vector<Proposition_Instance> propositions) {
		for (auto proposition : propositions) {
			auto result = find(true_propositions.begin(), true_propositions.end(), proposition);
			if (result != true_propositions.end()) {
				true_propositions.erase(result);
			}
		}
	}

	bool World::valuate(const Formula& formula) const {
		return formula.valuate(true_propositions);
	}

	const std::vector<Proposition_Instance> World::get_true_propositions() const {
		return true_propositions;
	}

	std::string World::to_string(const Domain& domain) const{
		std::string result = "World " + std::to_string(id.id) + ": ";
		bool first = true;
		for (auto proposition : true_propositions) {
			if (first) {
				first = false;
			} else {
				result += ";";
			}
			result += proposition.to_string(domain.get_id_to_atom());
		}
		return result;
	}
	void World::set_id(World_Id id) {
		this->id = std::move(id);
	}
}