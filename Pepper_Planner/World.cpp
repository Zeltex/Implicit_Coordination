#include "World.hpp"

namespace del {
	void World::add_true_proposition(std::string proposition) {
		true_propositions.insert(proposition);
	}
	void World::remove_true_proposition(std::string proposition) {
		true_propositions.erase(proposition);
	}

	bool World::valuate(Formula& formula) {
		return formula.valuate(true_propositions);
	}
}