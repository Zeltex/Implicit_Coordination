#include "Action_Event.hpp"

namespace del {

	Event_Id Action_Event::get_id() const {
		return id;
	}

	const std::unordered_set<std::string> Action_Event::get_add_list() const {
		return proposition_add;
	}

	const std::unordered_set<std::string> Action_Event::get_delete_list() const {
		return proposition_delete;
	}

	const Formula& Action_Event::get_preconditions() const {
		return precondition;
	}
}