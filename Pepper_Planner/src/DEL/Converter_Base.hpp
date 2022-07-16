#pragma once

#include "General_Proposition_Instance.hpp"
#include "Proposition_Instance.hpp"

#include <string>

namespace del
{
	class Agent;

	class Converter_Base
	{
	public:
		virtual const Proposition_Instance* convert(const General_Proposition_Instance* general_instance) const = 0;
		virtual const Agent* convert(const std::string& agent) const = 0;
	};
}