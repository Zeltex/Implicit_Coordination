#pragma once

#include <iostream>
#include <unordered_set>

#include "Types.hpp"
#include "Formula.hpp"

namespace del {
	class Domain;
	class World {
	public:

		World(World_Id id) : id(id), true_propositions(std::vector<Proposition_Instance>()) {}
		World(World_Id id, std::vector<Proposition_Instance> true_propositions) :
			id(id), true_propositions(true_propositions) {}

		World_Id get_id() const;
		void add_true_propositions(const std::vector<Proposition_Instance>& propositions);
		void remove_true_propositions(const std::vector<Proposition_Instance>& propositions);

		World create_copy(World_Id id) const;
		
		const std::vector<Proposition_Instance>& get_true_propositions() const;

		std::string to_string(const Domain& domain) const;
		void set_id(World_Id id);
		bool operator!=(const World& other) const;
		std::string to_hash() const;
	private:

		World_Id id;
		std::vector<Proposition_Instance> true_propositions;
	};
}