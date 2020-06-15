#include "Domain.hpp"

namespace del {

	void Domain::perform_do(const Agent_Id agent, const std::vector<std::string>& add_list, const std::vector<std::string>& delete_list) {

		std::unordered_set<std::string> add_set;
		for (auto proposition : add_list) {
			add_set.insert(proposition);
		}

		std::unordered_set<std::string> delete_set;
		for (auto proposition : delete_list) {
			delete_set.insert(proposition);
		}

		Formula f;
		f.f_top();
		Event_Id id{ 0 };
		Action_Event event = Action_Event(id, std::move(f), add_set, delete_set);


		Action action(agent, amount_of_agents);
		action.add_event(event);

		const State& current_state = states.back();
		states.push_back(perform_product_update(current_state, action));

	}

	void Domain::perform_action(Action action) {
		const State& current_state = states.back();
		states.push_back(perform_product_update(current_state, action));
	}

	State Domain::get_current_state() const {
		return states.back();
	}
}