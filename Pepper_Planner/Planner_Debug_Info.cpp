#include "Planner_Debug_Info.hpp"

namespace del 
{
	Debug_Info::Debug_Info(const Domain& domain)
		: or_layer_size(1), and_layer_size(1), domain(&domain)
	{ }

	void Debug_Info::print_final() const
	{
#if DEBUG_PRINT == 1
		report_memory_usage();
		print_debug_layer();
#endif
	}

	void Debug_Info::print_all() const
	{
#if DEBUG_PRINT == 1 && PRINT_PARTIAL == 0
		print_debug_layer();
#endif
	}

	void Debug_Info::print_single(const Node& node) const
	{
#if DEBUG_PRINT == 1 && PRINT_NODES == 1
		std::cout << "\nNode " << node.id << " at depth " << action_node.get_cost() << "\n";
		std::cout << node.to_string(domain) << std::endl;;
#endif
	}

	void Debug_Info::print_single(const Node_Id& node) const
	{
		print_single(graph->get_node(node));
	}

	void Debug_Info::update_and(const State& state)
	{
#if DEBUG_PRINT == 1
		const size_t cost = state.get_cost() / 100;
		if (and_layer_size.size() <= cost) {
			and_layer_size.push_back(0);
		}
		and_layer_size[cost] ++;
#endif
	}

	void Debug_Info::update_or(const State& state)
	{
#if DEBUG_PRINT == 1 ||1
		const size_t cost = state.get_cost() / 100;
		if (or_layer_size.size() <= cost) {
			or_layer_size.push_back(0);
		}
		or_layer_size[cost] ++;
#endif
	}

	void Debug_Info::print_debug_layer() const
	{
		std::string debug_print;
		size_t total_or_nodes = 0;
		size_t total_and_nodes = 0;
		for (size_t i = 0; i < or_layer_size.size(); ++i)
		{
			debug_print += std::to_string(i) + "(" + std::to_string(and_layer_size.at(i)) + ", " + std::to_string(or_layer_size.at(i)) + ") ";
			total_and_nodes += and_layer_size.at(i);
			total_or_nodes += or_layer_size.at(i);
		}
		std::cout << debug_print << "\nOr:" << total_or_nodes << ", and: " << total_and_nodes << std::endl;
	}
}