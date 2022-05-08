#include "Formula_Input_Impl.hpp"
#include "State.hpp"
#include "Domain.hpp"
#include "Propositions.hpp"

namespace del {

	bool Formula_Input_Impl::valuate_prop(const Proposition& prop, const size_t world_id) const 
	{
		if (state->is_true(world_id, prop)) 
		{
			return true;
		}

		if (domain != nullptr) {
			auto& propositions_domain = domain->get_atom_rigids();
			if (std::find(propositions_domain.begin(), propositions_domain.end(), prop) != propositions_domain.end()) {
				return true;
			}
		}
		return false;
	}
	
	std::set<size_t> Formula_Input_Impl::get_reachable_worlds(const Proposition& agent_id, size_t world_id) const {
		return state->get_reachable_worlds(agent_id.to_hash(), world_id);
	}

}