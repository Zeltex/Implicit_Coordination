#pragma once

#include <string>
#include <stdio.h>
#include <iostream>
#include <filesystem>

#include "Custom_Lexer.hpp"
#include "Custom_Parser.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"

namespace del
{
	class Test_Preparer
	{
	public:
		Test_Preparer(const std::string& file)
		{
			std::filesystem::remove(output_file);
			del_interface = new DEL_Interface(test_folder_path + file);
			propositions_lookup = &del_interface->get_propositions_lookup();
			atom_lookup = &del_interface->get_atom_lookup();
			agent_lookup = &del_interface->get_agent_lookup();
		}

		Proposition prop(const std::string& name, const std::string& arg_0)
		{
			return propositions_lookup->get(Proposition_Instance{ *atom_lookup, name, arg_0});
		}

		Proposition prop(const std::string& name, const std::string& arg_0, const std::string& arg_1)
		{
			return propositions_lookup->get(Proposition_Instance{ *atom_lookup, name, arg_0, arg_1});
		}

		Proposition prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2)
		{
			return propositions_lookup->get(Proposition_Instance{ *atom_lookup, name, arg_0, arg_1, arg_2});
		}

		Proposition prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3)
		{
			return propositions_lookup->get(Proposition_Instance{ *atom_lookup, name, arg_0, arg_1, arg_2, arg_3});
		}

		Proposition prop(const std::string& name, const std::string& arg_0, const std::string& arg_1, const std::string& arg_2, const std::string& arg_3, const std::string& arg_4)
		{
			return propositions_lookup->get(Proposition_Instance{ *atom_lookup, name, arg_0, arg_1, arg_2, arg_3, arg_4 });
		}

		Agent_Id agent(const std::string& name)
		{
			return agent_lookup->get(name).get_id();
		}

		bool query(const Formula& formula)
		{
			return del_interface->query(formula);
		}

		void perform(const std::string& name, const std::vector<std::string>& arguments)
		{
			del_interface->perform_action(name, arguments);
		}

		void print_state()
		{
			std::string print = del_interface->get_state_print();
			std::ofstream file;
			file.open(output_file, std::ios_base::app);
			file << print << std::endl;
			file.close();
			std::cout << print << std::endl;
		}

	private:

		DEL_Interface* del_interface;
		const Propositions_Lookup* propositions_lookup;
		const Atom_Lookup* atom_lookup;
		const Agents* agent_lookup;

		std::string test_folder_path = "../../Test_Cases/";
		std::string output_file = "output.txt";
	};
}