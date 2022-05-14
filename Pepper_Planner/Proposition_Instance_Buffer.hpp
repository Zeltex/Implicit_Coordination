#pragma once
#include <string>
#include <vector>
#include "Proposition_Instance.hpp"
#include "Variables_Buffer.hpp"
#include "Propositions.hpp"

namespace del
{
	class Inputs;
	class Proposition_Instance_Buffer
	{
	public:
		void set(Proposition_Instance_Buffer& other);
		void add(const std::string& name, Variables_Buffer& variables_buffer, const Inputs& inputs);
		//void push_proposition_instance(const std::string name, Variables_Buffer& variables_buffer, const Inputs& inputs);
		//Propositions get();
		std::vector<Proposition_Instance> get();
	private:

		std::map<Proposition_Instance, Proposition> instance_to_proposition;
		std::vector<Proposition_Instance> proposition_instances;
		Propositions propositions;
	};
}