#pragma once

#include "Formula.hpp"
#include "World.hpp"

namespace del {

	class State {
	public:
		bool valuate(Formula& formula);
	private:
		std::vector<World> worlds;
	};
}