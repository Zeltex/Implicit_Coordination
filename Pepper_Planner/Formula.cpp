#include "Formula.hpp"

namespace del {
	std::string Formula::to_string() {
		return formula->to_string();
	}
	bool Formula::valuate(std::unordered_set<std::string> propositions) {
		return formula->valuate(propositions);
	}
}