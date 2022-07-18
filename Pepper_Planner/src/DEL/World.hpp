#pragma once

#include "Types.hpp"
#include "Formula.hpp"
#include "Propositions.hpp"

namespace del {
	class Action_Event;
	class Atom_Lookup;
	class Domain;
	class General_World;
	class Propositions_Lookup;

	class World {
	public:

		World(const General_World& other, const Propositions_Lookup& propositions_lookup, const Atom_Lookup& atom_lookup);
		World(const World& other, const Action_Event& action, const World_Id& id);
		World(World_Id id) : id(id), true_propositions() {}
		World(World_Id id, const Propositions& true_propositions) :
			id(id), true_propositions(true_propositions) {}

		World_Id get_id() const;
		void add_true_propositions(const Propositions& propositions);
		void remove_true_propositions(const Propositions& propositions);
		
		const Propositions& get_true_propositions() const;

		std::string to_string() const;
		void set_id(World_Id id);
		bool operator!=(const World& other) const;
		std::string to_hash() const;
	private:

		World_Id id;
		Propositions true_propositions;
	};
}