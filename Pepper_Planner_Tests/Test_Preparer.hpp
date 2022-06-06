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

		DEL_Interface* del_interface;

		std::string test_folder_path = "../../Test_Cases/";
		std::string output_file = "output.txt";
	};
}