#pragma once

#include <iostream>
#include <unordered_set>

#include "Formula.hpp"

namespace del {
	class World {
	public:

		World() : true_propositions(std::unordered_set<std::string>()) {}

		void add_true_proposition(std::string proposition);
		void remove_true_proposition(std::string proposition);

		bool valuate(Formula& formula);

	private:
		std::unordered_set<std::string> true_propositions;
	};
}