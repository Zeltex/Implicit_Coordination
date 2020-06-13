#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include "Formula.hpp"

namespace del {
	class Action_Event {
	public:
		Action_Event(Event_Id id, Formula&& precondition, std::unordered_set<std::string> proposition_add, std::unordered_set<std::string> proposition_delete) :
			id(id), precondition(std::move(precondition)), proposition_add(proposition_add), proposition_delete(proposition_delete) {
			//precondition = std::move(precondition);
		}
		// precondition(std::move(precondition)),

		Event_Id get_id() const;
		const Formula& get_preconditions() const;
		const std::unordered_set<std::string> get_add_list() const;
		const std::unordered_set<std::string> get_delete_list() const;

		//Debug
		void increment_id() { id = Event_Id{ id.id  + 1}; };
	private:
		Event_Id id;
		Formula precondition;
		std::unordered_set<std::string> proposition_add;
		std::unordered_set<std::string> proposition_delete;

	};
}