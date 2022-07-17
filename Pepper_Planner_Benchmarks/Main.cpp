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

#include "MAPF_Benchmark.hpp"
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

	if (argc == 3)
	{
		size_t start_index = string_to_index(argv[1]);
		size_t end_index = string_to_index(argv[2]);

		if (start_index == -1 || end_index == -1)
		{
			std::cout << "Running benchmark '" << argv[1] << "'" << std::endl;
			del::run_benchmark(std::string(argv[1]), std::string(argv[2]));
			return 0;
		}
		else
		{
			std::cout << "Running MAPF benchmark from " << start_index << " to " << end_index << std::endl;
			del::run_mapf_benchmark("../Examples/MAPF/", start_index, end_index);
			return 0;
		}
	}

	std::cout << "Incorrect parameters, Format:" << std::endl;
	std::cout << "./Release/Pepper_Planner {filename} {planning_agent}" << std::endl;
	std::cout << "./Release/Pepper_Planner {mapf_start_index} {mapf_end_index}" << std::endl;
	std::cout << "Examples:" << std::endl;
	std::cout << "./Release/Pepper_Planner \"../Examples/MAPF/p1.maepl\" \"a0\"" << std::endl;
	std::cout << "./Release/Pepper_Planner 1 27" << std::endl;
	return 1;
}
