#include "World.hpp"

namespace del {

	World_Id World::get_id() const {
		return id;
	}

	World World::create_copy(World_Id id) const {
		return World(id, true_propositions);
	}

	//void World::add_true_propositions(const std::vector<std::string> propositions) {
	//	for (auto proposition : propositions) {
	//		true_propositions.insert(proposition);
	//	}
	//}

	void World::add_true_propositions(const std::unordered_set<std::string> propositions) {
		for (auto proposition : propositions) {
			true_propositions.insert(proposition);
		}
	}

	void World::remove_true_propositions(const std::unordered_set<std::string> propositions) {
		for (auto proposition : propositions) {
			true_propositions.erase(proposition);
		}
	}

	bool World::valuate(const Formula& formula) const {
		return formula.valuate(true_propositions);
	}

	const std::unordered_set<std::string> World::get_true_propositions() const {
		return true_propositions;
	}
}