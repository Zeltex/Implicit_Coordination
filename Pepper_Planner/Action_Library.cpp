#include "Action_Library.hpp"

namespace del {

	Action_Library::Action_Library(): announce_enabled(false), actions() {
	}

	Action_Library::Action_Library(size_t amount_of_agents) : announce_enabled(false), actions() {
		set_amount_of_agents(amount_of_agents);
	}

	void Action_Library::set_amount_of_agents(size_t amount_of_agents) {
		this->amount_of_agents = amount_of_agents;
	}

	const std::vector<Action>& Action_Library::get_actions() const{
		return actions;
	}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}

	void Action_Library::set_announce_enabled() {
		announce_enabled = true;
	}

	void Action_Library::add_general_action(const General_Action& general_action, const Domain& domain) {

		auto& owners = domain.get_all_atoms_of_type(general_action.get_owner());


		std::vector<std::vector<std::string>> atoms;
		std::vector<std::string> input_names;
		std::vector<size_t> counters;

		for (auto& entry : general_action.get_inputs()) {
			auto& temp = domain.get_all_atoms_of_type(entry.first);
			atoms.emplace_back(temp.begin(), temp.end());
			input_names.emplace_back(entry.second);
			counters.emplace_back(0);
		}

		for (auto& owner : owners) {
			for (auto& counter : counters) {
				counter = 0;
			}

			bool done = false;
			while (true) {

				std::unordered_map<std::string, std::string> input_to_atom;
				for (size_t i = 0; i < counters.size(); i++) {
					input_to_atom[input_names[i]] = atoms[i][counters[i]];
				}
				auto owner_id = domain.get_agent_id(owner);
				actions.emplace_back(general_action, owner_id, input_to_atom);


				counters[0]++;
				for (size_t i = 0; i < counters.size(); i++) {
					if (counters[i] >= atoms[i].size()) {
						if (i == counters.size() - 1) {
							done = true;
							break;
						}
						counters[i] = 0;
						counters[i + 1]++;
					} else {
						break;
					}
				}
				if (done) {
					break;
				}
			}
		}
	}
}