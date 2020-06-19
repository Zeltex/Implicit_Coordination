#pragma once

#include <iostream>
#include <unordered_set>

#include "Types.hpp"
#include "../Formula/Formula.hpp"

namespace del {
	class World {
	public:

		World(World_Id id) : id(id), true_propositions(std::unordered_set<std::string>()) {}
		World(World_Id id, std::unordered_set<std::string> true_propositions) : 
			id(id), true_propositions(true_propositions) {}

		World_Id get_id() const;
		//void add_true_propositions(const std::vector<std::string> propositions);
		void add_true_propositions(const std::unordered_set<std::string> propositions);
		void remove_true_propositions(const std::unordered_set<std::string> propositions);

		bool valuate(const Formula& formula) const;
		World create_copy(World_Id id) const;
		
		const std::unordered_set<std::string> get_true_propositions() const;

		std::string to_string() const;

	private:

		World_Id id;
		std::unordered_set<std::string> true_propositions;
	};
}