#include <unordered_set>

#include "Formula_Types.hpp"

namespace del {
	class Propositions {

		Propositions() : propositions() {}
		Propositions(const Propositions& propositions) : propositions(propositions.propositions) {}
		Propositions(const std::unordered_set<Proposition>& propositions) : propositions(propositions) {}
	private:
		std::unordered_set<Proposition> propositions;
	};
}