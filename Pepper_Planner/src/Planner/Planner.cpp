#include "Planner.hpp"

#include "Node_Comparator.hpp"
#include "Memory.hpp"
#include "Domain.hpp"
#include "Planner_Debug_Info.hpp"

#include <assert.h>

namespace del {

	// TODO - Node references may become invalid if more nodes are added to graph (du to vector reallocation), make sure this is not the case.

	// TODO - Check if we need to verify assumptions on initial state

	// TODO - Add option to specify for what person the goal must be fulfilled
	Policy Planner::find_policy(Domain& domain, 
								const Agent* planning_agent,
								const bool is_benchmark) const {
		const Formula& goal_formula = domain.get_goal();
		Action_Library& action_library = domain.get_action_library();

		const State& initial_state = domain.get_current_state();
		constexpr size_t initial_node_size = 10000;
		Node_Comparator history;
		Graph graph(initial_node_size, initial_state, history, planning_agent);
		Debug_Info debug_info(domain, graph);

		// TODO - Need to check if states in initial frontier are solved
		while (!graph.is_frontier_empty()) 
		{
			debug_info.print_all();
			
			NodeOr* current_node = graph.get_next_from_frontier();
			debug_info.print_single(current_node);
			action_library.load_actions();
			std::vector<std::set<World_Id>> perspective_shifts = current_node->get_all_perspectives(domain.get_agents());

			while (action_library.has_action()) 
			{
				const Action* action = action_library.get_next_action();
				assert(action->get_owner()->get_id().id < perspective_shifts.size());
				auto& perspective = perspective_shifts.at(action->get_owner()->get_id().id);
				std::optional<State> temp_state = current_node->product_update(action, domain, perspective);
				if (!temp_state.has_value())
				{
					continue;
				}

				State state_product_update = temp_state.value().contract();

				if (history.does_bisimilar_exist(state_product_update, current_node, action))
				{
					continue;
				}

				NodeAnd* action_node = graph.create_and_node(state_product_update, current_node, action);
				debug_info.print_single(action_node);
				history.insert(action_node);
				debug_info.update_and(state_product_update);

				auto globals = state_product_update.split_into_globals();
				for (State& global_state : globals) 
				{
					if (history.does_bisimilar_exist(global_state, action_node))
					{
						continue;
					}

					debug_info.update_or(global_state);
					NodeOr* global_agent_node = graph.create_or_node(std::move(global_state), action_node);
					if (global_agent_node->is_goal(goal_formula, domain)) 
					{
						global_agent_node->set_solved();
					} 
					else 
					{
						graph.add_to_frontier(global_agent_node);
					}
					history.insert(global_agent_node);
				}
				action_node->propagate_solved();
			}
			current_node->propagate_solved();
			current_node->propagate_dead();

			auto policy = check_root(graph, is_benchmark);
			if (policy.has_value()) 
			{
				debug_info.print_final();
				return policy.value();
			}
		}
		debug_info.print_final();
		std::cout << "No policy found\n";
		std::cout << graph.to_string(domain);
		return Policy(false);
	}

	std::optional<Policy> Planner::check_root(Graph& graph, const bool is_benchmark) const 
	{
		if (graph.get_root_node()->is_dead()) 
		{
			std::cout << "No policy found\n";
			return Policy(false);
		}
		
		if (graph.get_root_node()->is_solved()) {
			std::cout << "Policy found\n";
			std::cout << "is benchmark " << is_benchmark <<  std::endl;
			if (is_benchmark) {
				return Policy(true);
			} else 
			{
				graph.calculate_value();
				Policy policy(true);
				graph.get_root_node()->extract_policy(policy);
				return policy;
			}
		}
		return {};
	}
}
