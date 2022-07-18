#define __STDC_WANT_LIB_EXT1__ 1
#define _CRT_SECURE_NO_WARNINGS 1

#include <string>
#include <math.h>
#include <unordered_set>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include <time.h>
#include <stdio.h>
#include <stdlib.h> 
#include <ctime>    
#include <numeric>

#include "Run.hpp"
#include "Utils.h"

int string_to_index(char* arg)
{
	if (arg[0] < '0' || arg[0] > '9')
	{
		return -1;
	}

	return strlen(arg) >= 2
		? 10 * (arg[0] - '0') + (arg[1] - '0')
		: arg[0] - '0';
}
	
int main(int argc, char* argv[])
{
	if (argc == 1)
	{
		size_t start_index = 1;
		size_t end_index = 27;

		std::cout << "Running MAPF benchmark from " << start_index << " to " << end_index << std::endl;
		del::run_mapf_benchmark("../Examples/MAPF/", start_index, end_index);
		return 0;
	}

	if (argc == 4)
	{
		std::string type(argv[1]);
		if (type == "mapf")
		{
			size_t start_index = string_to_index(argv[2]);
			size_t end_index = string_to_index(argv[3]);
			if (start_index != -1 && end_index != -1)
			{
				del::run_mapf_benchmark("../Examples/MAPF/", start_index, end_index);
				return 0;
			}
		}
		else if (type == "coin")
		{
			size_t start_index = string_to_index(argv[2]);
			size_t end_index = string_to_index(argv[3]);
			if (start_index != -1 && end_index != -1)
			{
				del::run_coin_flip_benchmark("../Examples/Coin_Flip/", start_index, end_index);
				return 0;
			}

		}
		else if (type == "single")
		{

			std::cout << "Running benchmark '" << argv[1] << "'" << std::endl;
			del::run_single_benchmark(std::string(argv[2]), std::string(argv[3]));
			return 0;
		}
	}

	std::cout << "Incorrect parameters, Format:" << std::endl;
	std::cout << "./Release/Pepper_Planner single {filename} {planning_agent}" << std::endl;
	std::cout << "./Release/Pepper_Planner mapf {mapf_start_index} {mapf_end_index}" << std::endl;
	std::cout << "./Release/Pepper_Planner coin {mapf_start_index} {mapf_end_index}" << std::endl;
	std::cout << "Examples:" << std::endl;
	std::cout << "./Release/Pepper_Planner single \"../Examples/MAPF/p1.maepl\" \"a0\"" << std::endl;
	std::cout << "./Release/Pepper_Planner mapf 1 27" << std::endl;
	std::cout << "./Release/Pepper_Planner coin 1 27" << std::endl;
	return 1;
}
