#pragma once

#include "Types.hpp"
#include "Formula.hpp"
#include "Propositions.hpp"

namespace del
{
	class Action_Event;
	class Converter_Base;
	class General_World;
	struct Proposition_Instance;

	class World
	{
	public:
		World(const General_World& other, const Converter_Base* converter);
		World(const World& other, const Action_Event& action, const World_Id& id);
		World(World_Id id, const Propositions& true_propositions);

		World_Id			get_id() const;
		const Propositions& get_true_propositions() const;
		bool				is_true(const Proposition_Instance* proposition) const;
		std::string			to_hash() const;
		std::string			to_string() const;

		bool operator!=(const World& other) const;
	private:

		World_Id id;
		Propositions true_propositions;
	};
}