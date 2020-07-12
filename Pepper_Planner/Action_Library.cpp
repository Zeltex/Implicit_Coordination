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

	const General_Action& Action_Library::get_general_action(std::string name) const {
		return general_actions.at(general_action_name_to_id.at(name));
	}

	const std::vector<Action> Action_Library::get_announce_actions(State state, const Domain& domain) const {
		std::vector<Action> result;
		
		if (!announce_enabled) {
			return result;
		}
		// TODO - Maybe take into account if some of the worlds are runtime distinguishable, i.e. allowing to announce more beliefs
		for (size_t agent = 0; agent < state.get_number_of_agents(); agent++) {
			auto reachables = state.get_designated_world_reachables({ agent });
			if (reachables.empty()) {
				continue;
			}
			auto propositions_to_announce = state.get_world(reachables[0]).get_true_propositions();
			for (auto world : reachables) {
				if (propositions_to_announce.empty()) {
					break;
				}
				auto propositions = state.get_world(world).get_true_propositions();
				std::vector<size_t> to_delete;
				size_t counter = 0;
				for (auto entry : propositions_to_announce) {
					if (find(propositions.begin(), propositions.end(), entry) == propositions.end()) {
						to_delete.push_back(counter);
					}
					counter++;
				}
				for (auto iterator = to_delete.rbegin(); iterator != to_delete.rend(); iterator++) {
					propositions_to_announce.erase(propositions_to_announce.begin() + *iterator);
				}

			}
			for (auto proposition : propositions_to_announce) {
				result.push_back(create_announce_action({ agent }, proposition, state.get_number_of_agents(), domain));
			}
		}
		return std::move(result);
		
	}

	Action Action_Library::create_announce_action(Agent_Id owner, Proposition_Instance proposition, size_t amount_of_agents, const Domain& domain) const {
		// TODO - Figure out how to handle announce actions

		// TODO - Could probably optimise by checking if observers/unaware sets are empty

		// TODO - Action owner should always have status of perceiving the action

		Action action(owner, amount_of_agents);

		action.set_cost(ANNOUNCE_COST);


		Formula f1;
		f1.f_prop(proposition);
		Action_Event event1 = Action_Event(Event_Id { 0 }, std::move(f1), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
		action.add_event(event1);

		Formula f2;
		f2.f_not(f2.f_prop(proposition));
		Action_Event event2 = Action_Event(Event_Id { 1 }, std::move(f2), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
		action.add_event(event2);

		Formula f3;
		f3.f_top();
		Action_Event event3 = Action_Event(Event_Id{ 2 }, std::move(f3), std::vector<Proposition_Instance>(), std::vector<Proposition_Instance>());
		action.add_event(event3);

		for (auto& agent : domain.get_agents()) {
			// Perceives
			for (size_t event : { 0, 1 }) {
				Formula condition;
				auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
				auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
				condition.f_or({ perceives, observes });
				action.add_reachability(agent.get_id(), { event }, { event }, std::move(condition));
			}

			// Observes
			for (size_t event_from : { 0, 1 }) {
				for (size_t event_to : { 0, 1 }) {
					if (event_from == event_to) continue;
					Formula condition;
					auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
					auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
					auto not_perceives = condition.f_not(perceives);
					condition.f_and({ observes, not_perceives });

					action.add_reachability(agent.get_id(), { event_from }, { event_to }, std::move(condition));
				}
			}

			// Unaware
			for (size_t event : { 0, 1 }) {
				Formula condition;
				auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
				auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
				auto not_observes = condition.f_not(observes);
				auto not_perceives = condition.f_not(perceives);
				condition.f_and({ not_observes, not_perceives });

				action.add_reachability(agent.get_id(), { event }, { 2 }, std::move(condition));
			}

			// Unaware reflexive
			Formula condition;
			condition.f_top();
			action.add_reachability(agent.get_id(), { 2 }, { 2 }, std::move(condition));
		}


		action.add_designated_event(Event_Id{ 0 });
		action.add_designated_event(Event_Id{ 1 });
		return action;
	}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}

	void Action_Library::set_announce_enabled() {
		announce_enabled = true;
	}

	void Action_Library::add_general_action(const General_Action& general_action, const Domain& domain) {

		general_actions.push_back(general_action);
		general_action_name_to_id[general_action.get_name()] = general_actions.size() - 1;

		std::pair<std::string, Atom_Id> action_owner = general_action.get_owner();
		auto& owners = domain.get_all_atoms_of_type(action_owner.first);


		std::vector<std::vector<Atom_Id>> atoms;
		std::vector<Atom_Id> input_names;
		std::vector<size_t> counters;

		size_t owner_input_index = general_action.get_inputs().size();

		size_t index = 0;
		for (auto& entry : general_action.get_inputs()) {
			auto& temp = domain.get_all_atoms_of_type(entry.first);
			atoms.emplace_back(temp.begin(), temp.end());
			input_names.emplace_back(entry.second);
			counters.emplace_back(0);

			if (entry.second == action_owner.second) {
				owner_input_index = index;
			}
			index++;
		}

		for (auto& owner : owners) {
			for (auto& counter : counters) {
				counter = 0;
			}

			bool done = false;
			while (true) {

				//std::unordered_map<std::string, std::string> input_to_atom;
				std::vector<Atom_Id> arguments;
				bool valid_owner_input = true;
				for (size_t i = 0; i < counters.size(); i++) {
					//input_to_atom[input_names[i]] = atoms[i][counters[i]];
					arguments.emplace_back(atoms[i][counters[i]]);
					if (i == owner_input_index && owner != atoms[i][counters[i]].id) {
						valid_owner_input = false;
					}
				}
				if (valid_owner_input) {
					auto owner_id = domain.get_agent_id(owner);
					actions.emplace_back(general_action.create_action(owner, arguments, domain));
					//actions.emplace_back(general_action, owner_id, input_to_atom);
				}

				if (!increment_counters_success(counters, atoms)) {
					break;
				}
			}
		}
	}

	bool Action_Library::increment_counters_success(std::vector<size_t>& counters, std::vector<std::vector<Atom_Id>>& atoms) {
		counters[0]++;
		for (size_t i = 0; i < counters.size(); i++) {
			if (counters[i] >= atoms[i].size()) {
				if (i == counters.size() - 1) {
					return false;
				}
				counters[i] = 0;
				counters[i + 1]++;
			} else {
				return true;
			}
		}
		return true;
	}
}