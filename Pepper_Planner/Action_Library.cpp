#include "Action_Library.hpp"

namespace del {

	Action_Library::Action_Library(): amount_of_agents(0), action_counter(0), announce_enabled(false), actions() {
	}

	Action_Library::Action_Library(size_t amount_of_agents) : action_counter(0), announce_enabled(false), actions() {
		set_amount_of_agents(amount_of_agents);
	}


	void Action_Library::load_actions(const State& state, const Domain& domain) {
		// TODO - These actions should be saved in a map so that each action is only generated once
		//announce_actions = std::move(get_announce_actions(state, domain));
		action_counter = 0;
	}

	bool Action_Library::has_action() const {
		return action_counter < actions.size() + announce_actions.size();
	}

	const Action& Action_Library::get_next_action() {
		size_t temp_counter = action_counter++;
		if (temp_counter < actions.size()) {
			return actions.at(temp_counter);
		} else {
			return announce_actions.at(temp_counter - actions.size());
		}
	}

	void Action_Library::set_amount_of_agents(size_t amount_of_agents) {
		this->amount_of_agents = amount_of_agents;
	}

	const std::vector<Action>& Action_Library::get_actions() const{
		return actions;
	}

	const General_Action& Action_Library::get_general_action(const std::string& name) const {
		return general_actions.at(general_action_name_to_id.at(name));
	}

	//std::vector<Action> Action_Library::get_announce_actions(const State& state, const Domain& domain) const {
	//	std::vector<Action> result;
	//	
	//	if (!announce_enabled) {
	//		return result;
	//	}

	//	for (size_t agent = 0; agent < state.get_number_of_agents(); agent++) {
	//		auto reachables = state.get_designated_world_reachables({ agent });
	//		if (reachables.empty()) {
	//			continue;
	//		}
	//		auto propositions_to_announce = state.get_world(reachables[0]).get_true_propositions();
	//		for (auto world : reachables) {
	//			if (propositions_to_announce.empty()) {
	//				break;
	//			}
	//			const auto& propositions = state.get_world(world).get_true_propositions();
	//			std::vector<size_t> to_delete;
	//			size_t counter = 0;
	//			for (auto entry : propositions_to_announce) {
	//				if (find(propositions.begin(), propositions.end(), entry) == propositions.end()) {
	//					to_delete.push_back(counter);
	//				}
	//				counter++;
	//			}
	//			for (auto iterator = to_delete.rbegin(); iterator != to_delete.rend(); iterator++) {
	//				propositions_to_announce.erase(propositions_to_announce.begin() + *iterator);
	//			}

	//		}
	//		for (const auto& proposition : propositions_to_announce) {
	//			result.push_back(create_announce_action({ agent }, proposition, state.get_number_of_agents(), domain));
	//		}
	//	}
	//	return std::move(result);
	//	
	//}

	//Action Action_Library::create_announce_action(Agent_Id owner, const Proposition& proposition, size_t amount_of_agents, const Domain& domain) const {
	//	// TODO - Figure out how to handle announce actions

	//	// TODO - Could probably optimise by checking if observers/unaware sets are empty

	//	// TODO - Action owner should always have status of perceiving the action

	//	Action action(owner, amount_of_agents);

	//	action.set_cost(ANNOUNCE_COST);
	//	action.set_name("Announce");


	//	Formula f1;
	//	f1.f_prop(proposition);
	//	Action_Event event1 = Action_Event(Event_Id { 0 }, std::move(f1), std::vector<Proposition>(), std::vector<Proposition>());
	//	action.add_event(event1);

	//	Formula f2;
	//	f2.f_not(f2.f_prop(proposition));
	//	Action_Event event2 = Action_Event(Event_Id { 1 }, std::move(f2), std::vector<Proposition>(), std::vector<Proposition>());
	//	action.add_event(event2);

	//	Formula f3;
	//	f3.f_top();
	//	Action_Event event3 = Action_Event(Event_Id{ 2 }, std::move(f3), std::vector<Proposition>(), std::vector<Proposition>());
	//	action.add_event(event3);

	//	for (auto& agent : domain.get_agents()) {
	//		// Perceives
	//		for (size_t event : { 0, 1 }) {
	//			Formula condition;
	//			auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//			auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//			condition.f_or({ perceives, observes });
	//			action.add_reachability(agent.get_id(), { event }, { event }, std::move(condition));
	//		}

	//		// Observes
	//		for (size_t event_from : { 0, 1 }) {
	//			for (size_t event_to : { 0, 1 }) {
	//				if (event_from == event_to) continue;
	//				Formula condition;
	//				auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//				auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//				auto not_perceives = condition.f_not(perceives);
	//				condition.f_and({ observes, not_perceives });

	//				action.add_reachability(agent.get_id(), { event_from }, { event_to }, std::move(condition));
	//			}
	//		}

	//		// Unaware
	//		for (size_t event : { 0, 1 }) {
	//			Formula condition;
	//			auto observes = condition.f_prop({ OBSERVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//			auto perceives = condition.f_prop({ PERCEIVES, {agent.get_atom_id(), domain.get_agent(owner).get_atom_id()} });
	//			auto not_observes = condition.f_not(observes);
	//			auto not_perceives = condition.f_not(perceives);
	//			condition.f_and({ not_observes, not_perceives });

	//			action.add_reachability(agent.get_id(), { event }, { 2 }, std::move(condition));
	//		}

	//		// Unaware reflexive
	//		Formula condition;
	//		condition.f_top();
	//		action.add_reachability(agent.get_id(), { 2 }, { 2 }, std::move(condition));
	//	}


	//	action.add_designated_event(Event_Id{ 0 });
	//	action.add_designated_event(Event_Id{ 1 });
	//	return action;
	//}

	void Action_Library::add_action(const Action& action) {
		actions.push_back(action);
	}

	void Action_Library::set_announce_enabled() {
		announce_enabled = true;
	}

	void Action_Library::add_general_action(const General_Action& general_action, const Domain& domain) {

		general_actions.push_back(general_action);
		general_action_name_to_id[general_action.get_name()] = general_actions.size() - 1;

		std::vector<std::vector<Atom_Id>> atoms;
		std::vector<size_t> counters;

		// Load all combinations of input
		for (auto& entry : general_action.get_inputs()) {
			auto& temp = domain.get_all_atoms_of_type(entry.first);
			atoms.emplace_back(temp.begin(), temp.end());
			counters.emplace_back(0);
		}

		// Generate all possible valid inputs
		bool done = false;
		while (!done) {

			std::vector<Atom_Id> arguments;
			for (size_t i = 0; i < counters.size(); i++) {
				arguments.emplace_back(atoms[i][counters[i]]);
			}
			Action(general_action, domain, arguments);
			actions.emplace_back(general_action, domain, arguments);

			// Advance indices
			size_t index = 0;
			while (!done && ++counters.at(index) >= atoms.at(index).size()) {
				counters.at(index++) = 0;
				done = index >= counters.size();
			}
		}
	}
}