#pragma once

#include <iostream>
#include <unordered_set>

#include "Types.hpp"
#include "../Formula/Formula.hpp"

namespace del {
	class World {
	public:

		World(World_Id id) : id(id), true_propositions(std::vector<Proposition_Instance>()) {}
		World(World_Id id, std::vector<Proposition_Instance> true_propositions) :
			id(id), true_propositions(true_propositions) {}

		World_Id get_id() const;
		//void add_true_propositions(const std::vector<std::string> propositions);
		void add_true_propositions(const std::vector<Proposition_Instance> propositions);
		void remove_true_propositions(const std::vector<Proposition_Instance> propositions);

		bool valuate(const Formula& formula) const;
		World create_copy(World_Id id) const;
		
		const std::vector<Proposition_Instance> get_true_propositions() const;

		std::string to_string() const;

	private:

		World_Id id;
		std::vector<Proposition_Instance> true_propositions;
	};
}