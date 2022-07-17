#pragma once

#include "General_Proposition_Instance.hpp"
#include "Propositions.hpp"

#include <map>
#include <string>
#include <vector>

namespace del
{
	class Propositions_Lookup;
	class Variables_Buffer;

	class Proposition_Instance_Buffer
	{
	friend class Propositions;
	public:
		Proposition_Instance_Buffer();
		void set(Proposition_Instance_Buffer& other);
		void set_and_consume(Proposition_Instance_Buffer& other);
		void add(const std::string& name, Variables_Buffer& variables_buffer);
		Proposition_Instance_Buffer move();
		std::vector<General_Proposition_Instance> get();
	private:

		std::vector<General_Proposition_Instance> proposition_instances;
	};
}