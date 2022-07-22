#pragma once
#include "CppUnitTest.h"

#include <string>
#include <stdio.h>
#include <iostream>
#include <filesystem>

#include "Atom_Lookup.hpp"
#include "Custom_Lexer.hpp"
#include "Custom_Parser.hpp"
#include "Domain.hpp"
#include "DEL_Interface.hpp"
#include "General_State.hpp"
#include "General_Typed_Propositions.hpp"
#include "Proposition_Instance_Buffer.hpp"
#include "Propositions_Lookup.hpp"
#include "Types.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace del
{
	class Test_Preparer
	{
	public:
		Test_Preparer(const std::string& file)
		{
			std::filesystem::remove(output_file);
			del_interface = new DEL_Interface(test_folder_path + file);
		}

		void print_state()
		{
			print(del_interface->get_state_print());

		}

		void print_action(const Action* action)
		{
			print(del_interface->get_action_print(action));
		}

		void print_policy()
		{
			print(del_interface->get_policy_print());
		}

		void execute_until_solved()
		{
			print_state();
			while (!del_interface->is_solved())
			{
				auto next_action = del_interface->get_next_action();
				Assert::IsTrue(next_action != nullptr);
				del_interface->perform_action(next_action);

				print_action(next_action);
				//print_state();
			}
			Assert::IsTrue(del_interface->is_solved());
		}

	private:
		void print(const std::string& print)
		{
			std::ofstream file;
			file.open(output_file, std::ios_base::app);
			file << print << std::endl << std::endl;
			file.close();
			std::cout << print << std::endl << std::endl;
		}

	public:
		DEL_Interface* del_interface;

	private:
		std::string test_folder_path = "../../Test_Cases/";
		std::string output_file = "output.txt";

	};
}