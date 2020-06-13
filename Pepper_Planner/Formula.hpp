#pragma once

#include <string>
#include <vector>
#include <unordered_set>

#include "Types.hpp"
#include "Formula_Component.hpp"

namespace del {

	class Formula {
	public:
		Formula_Component* formula;

		~Formula() { delete formula; }
		Formula() = delete;
		Formula(Formula_Component* formula) : formula(formula) {};

		std::string to_string();
		bool valuate(std::unordered_set<std::string> propositions);
	private:
	};
	
}