#pragma once

#include <vector>
#include <string>

#include "Formula_Types.hpp"
#include "General_Proposition_Instance.hpp"
#include "Loader_Types.hpp"
#include "Proposition_Instance.hpp"
#include "Types.hpp"


namespace del {
	class General_World {
	friend class World;
	public:
		General_World(const std::string& name, World_Id world_id, std::vector<General_Proposition_Instance> propositions);
		const std::string& get_name() const;
		World_Id get_id() const;
	private:
		World_Id world_id;
		std::string name;
		std::vector<General_Proposition_Instance> propositions;
	};
}