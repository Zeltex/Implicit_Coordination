#pragma once

#include <vector>
#include "State.hpp"
#include "Domain.hpp"
#include "Node.hpp"
#include "Types.hpp"
#include "Graph.hpp"
namespace del
{
	class Debug_Info
	{
	public:
		Debug_Info(const Domain& domain, const Graph& graph);
		void print_final() const;
		void print_all() const;
		void print_single(const Node& node) const;
		void print_single(const Node_Id& node) const;
		void update_and(const State& state);
		void update_or(const State& state);
	private:

		void print_debug_layer() const;

		std::vector<size_t> or_layer_size;
		std::vector<size_t> and_layer_size;
		const Domain* domain;
		const Graph* graph;

	};

}