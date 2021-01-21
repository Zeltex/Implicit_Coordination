#include "Action_Event.hpp"
#include "Domain.hpp"

namespace del {

	Event_Id Action_Event::get_id() const {
		return id;
	}

	const std::vector<Proposition> Action_Event::get_add_list() const {
		return proposition_add;
	}

	const std::vector<Proposition> Action_Event::get_delete_list() const {
		return proposition_delete;
	}

	const Formula& Action_Event::get_preconditions() const {
		return precondition;
	}

	std::string Action_Event::get_name() const {
		return name;
	}

	std::string Action_Event::to_string(const Domain& domain) const {
		std::string result = "Event " + std::to_string(id.id) + ": (Preconditions: " + precondition.to_string(domain.get_id_to_atom()) + ") (Add list";
		for (auto add : proposition_add) {
			result += ", " + domain.get_proposition_instance(add).to_string(domain.get_id_to_atom());
		}
		result += ") (Delete list, ";
		for (auto delete_entry : proposition_delete) {
			result += ", " + domain.get_proposition_instance(delete_entry).to_string(domain.get_id_to_atom());
		}
		result += ")";
		return result;
	}

}