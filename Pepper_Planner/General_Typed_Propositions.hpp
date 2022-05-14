#pragma once
#include <vector>
#include <string>

namespace del
{
	class Inputs_Buffer;
	class Inputs;

	// E.g. at(agent, pos)
	class General_Typed_Proposition
	{
	public:
		General_Typed_Proposition(const std::string& name, std::vector<std::string> type_inputs);
	private:
		std::string name;
		std::vector<std::string> type_inputs;
	};

	class General_Typed_Propositions
	{
	public:
		void add(const std::string& name, Inputs_Buffer& inputs_buffer);
	private:
		std::vector<General_Typed_Proposition> propositions;
	};
}