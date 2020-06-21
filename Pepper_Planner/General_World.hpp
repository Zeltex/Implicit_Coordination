#pragma once

#include <vector>
#include <string>

#include "../Domain_Loader/Types.hpp"

namespace del {
	class General_World {
	public:
		General_World(std::string name, std::vector<Proposition_Instance> propositions) : name(name), propositions(propositions) {}
	private:
		std::string name;
		std::vector<Proposition_Instance> propositions;
	};
}