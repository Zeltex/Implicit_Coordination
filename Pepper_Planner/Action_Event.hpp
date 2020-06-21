#pragma once

#include <vector>
#include <string>
#include <unordered_set>

#include "Types.hpp"
#include "../Formula/Formula.hpp"

namespace del {
	class Action_Event {
	public:
		Action_Event(Event_Id id, Formula&& precondition, std::vector<Proposition_Instance> proposition_add, std::vector<Proposition_Instance> proposition_delete) :
			id(id), precondition(std::move(precondition)), proposition_add(proposition_add), proposition_delete(proposition_delete) {
			//precondition = std::move(precondition);
		}
		// precondition(std::move(precondition)),

		Event_Id get_id() const;
		const Formula& get_preconditions() const;
		const std::vector<Proposition_Instance> get_add_list() const;
		const std::vector<Proposition_Instance> get_delete_list() const;


		std::string to_string() const;

	private:
		Event_Id id;
		Formula precondition;
		std::vector<Proposition_Instance> proposition_add;
		std::vector<Proposition_Instance> proposition_delete;

	};
}