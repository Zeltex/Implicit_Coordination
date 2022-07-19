#include "World.hpp"

#include "Action_Events.hpp"
#include "Atom_Lookup.hpp"
#include "Domain.hpp"
#include "General_World.hpp"
#include "Propositions_Lookup.hpp"

namespace del
{

	World::World(const General_World& other, const Converter_Base* converter)
		: id(other.world_id),
		true_propositions(other.propositions, converter)
	{

	}

	World::World(const World& other, const Action_Event& action, const World_Id& id)
		: id(id),
		true_propositions(other.get_true_propositions(), action.get_delete_list(), action.get_add_list())
	{

	}

	World::World(World_Id id, const Propositions& true_propositions) :
		id(id), true_propositions(true_propositions)
	{
	}

	World_Id World::get_id() const
	{
		return id;
	}

	bool World::is_true(const Proposition_Instance* proposition) const
	{
		return true_propositions.contains(proposition);
	}

	const Propositions& World::get_true_propositions() const
	{
		return true_propositions;
	}

	std::string World::to_string() const
	{
		return "World " + std::to_string(id.id) + ": " + true_propositions.to_string();
	}

	bool World::operator!=(const World& other) const
	{
		return true_propositions != other.true_propositions;
	}

	std::string World::to_hash() const
	{
		return true_propositions.to_hash();
	}
}