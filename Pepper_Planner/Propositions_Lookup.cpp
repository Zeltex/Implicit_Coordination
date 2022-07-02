#include "Propositions_Lookup.hpp"

#include "Atom_Lookup.hpp"
#include "General_Typed_Propositions.hpp"
#include "General_State.hpp"
#include "Proposition_Instance_Buffer.hpp"

#include <assert.h>

namespace del
{
	Propositions_Lookup::Propositions_Lookup(const General_Typed_Propositions& typed_propositions, const Atom_Lookup& atom_lookup, const General_State& state, const Proposition_Instance_Buffer& proposition_instance_buffer)
	{

		for (const General_Typed_Proposition& Typed_Proposition : typed_propositions)
		{

			// Convert object set to indicable list
			std::vector<std::vector<std::string>> list_atoms;
			const std::vector<std::string>& inputs = Typed_Proposition.type_inputs;
			for (const std::string& input : inputs) 
			{
				list_atoms.emplace_back();
				for (const Atom& atom : atom_lookup.get_atoms(input)) 
				{
					list_atoms.back().push_back(atom.get_name());
				}
			}

			// Produce all grounded propositions
			std::vector<size_t> indices(list_atoms.size());
			bool done = false;
			while (!done) {
				Atoms grounded_input;
				for (size_t i = 0; i < indices.size(); ++i) {
					const std::string& input_type = inputs.at(i);
					const std::string& atom = list_atoms.at(i).at(indices.at(i));
					grounded_input.insert(atom_lookup.get_atom(atom));
				}
				Proposition_Instance instance{Typed_Proposition.name, grounded_input };
				size_t id = instance_to_proposition.size();
				instance_to_proposition.insert({ instance, id});
				proposition_to_instance.insert({ id, instance });

				// Advance indices
				size_t index = 0;
				while (!done && ++indices.at(index) >= list_atoms.at(index).size()) {
					indices.at(index++) = 0;
					done = index >= indices.size();
				}
			}
		}
	}

	const Proposition& Propositions_Lookup::get(const Proposition_Instance& instance) const
	{
		assert(instance_to_proposition.find(instance) != instance_to_proposition.end());
		return instance_to_proposition.at(instance);
	}

	const Proposition_Instance& Propositions_Lookup::get_instance(const Proposition& proposition) const
	{
		assert(proposition_to_instance.find(proposition) != proposition_to_instance.end());
		return proposition_to_instance.at(proposition);
	}
}