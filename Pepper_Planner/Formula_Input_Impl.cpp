#include "Formula_Input_Impl.hpp"
#include "State.hpp"
#include "Domain.hpp"

namespace del {

	bool Formula_Input_Impl::valuate_prop(Proposition_Instance prop, const size_t world_id) const {
		auto& propositions_state = state->get_true_propositions(world_id);
		if (std::find(propositions_state.begin(), propositions_state.end(), prop) != propositions_state.end()) return true;
		if (domain != nullptr) {
			auto& propositions_domain = domain->get_atom_rigids();
			if (std::find(propositions_domain.begin(), propositions_domain.end(), prop) != propositions_domain.end()) {
				return true;
			}
		}
		return false;
	}
	
	std::vector<size_t> Formula_Input_Impl::get_reachable_worlds(size_t agent_id, size_t world_id) const {
		return state->get_reachable_worlds(agent_id, world_id);
	}

}