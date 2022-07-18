#include "Run.hpp"

#include "DEL_Interface.hpp"
#include "Utils.h"

#include <chrono>
#include <filesystem>

namespace del {
	void run_benchmark(const std::vector<std::string>& file_paths, const std::string& planning_agent, const std::string& output_file, bool execute_problems)
	{
		std::vector<long long> times;
		std::vector<std::string> files;
		bool is_benchmark = !execute_problems;
		bool all_solved = true;
		bool all_executions_successfull = true;
		std::string output_dir = output_file.substr(0, output_file.find_last_of("/\\"));

		if (!std::filesystem::exists(output_dir))
		{
			std::filesystem::create_directory(output_dir);
		}

		for (auto& file_path : file_paths)
		{
			size_t slash_index = file_path.find_last_of("/\\");
			std::string file = file_path.substr(slash_index + 1, file_path.length() - slash_index - 1);
			files.push_back(file);
			DEL_Interface del_interface(file_path);
			auto time_start = std::chrono::high_resolution_clock::now();
			bool solved = del_interface.create_policy(planning_agent, is_benchmark);
			auto time_end = std::chrono::high_resolution_clock::now();

			all_solved &= solved;

			times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count());
			std::cout 
				<< file 
				<< " took ms " 
				<< times.back() 
				<< (execute_problems ? "(including policy extraction)" : "") 
				<< ", solved = " 
				<< solved 
				<< std::endl 
				<< std::endl;

			std::string actions_string;
			if (execute_problems)
			{
				bool failed = false;
				size_t iterations = 0;
				while (!del_interface.is_solved() && !failed && iterations++ < 100)
				{
					const Action* action = del_interface.get_next_action();
					if (action != nullptr)
					{
						actions_string += action->to_string() + "\n";
						if (!del_interface.perform_action(action))
						{
							actions_string += "Action is inapplicable\n";
							failed = true;
						}
					}
					else
					{
						actions_string += "No applicable action\n";
						failed = true;
					}
				}
				
				if (failed)
				{
					all_executions_successfull = false;
					actions_string += "Failed to perform actions from policy\n";
				}
				std::cout << actions_string;
			}


			std::ofstream output;
			output.open(output_file);
			if (execute_problems)
			{
				output << "Times include policy extraction" << std::endl;
				output << "All problem executions successfull = " << all_executions_successfull << std::endl;
			}
			
			output << "All problems solved = " << all_solved << std::endl;

			for (size_t j = 0; j < times.size(); ++j)
			{
				output << files.at(j) << ";" << times.at(j) << " ms" << std::endl;
			}
	
			if (!actions_string.empty())
			{
				output << actions_string << std::endl;
			}

			output.close();

		}
	}

	void run_mapf_benchmark(const std::string& folder, size_t start_index, size_t end_index) {
		std::string planning_agent = "a0";
		std::vector<std::string> file_paths;
		std::string output_file = "../Benchmarks/Benchmarks_mapfdu.csv";

		for (size_t i = start_index; i <= end_index; ++i) {
			file_paths.push_back(folder + "p" + std::to_string(i) + ".maepl");
		}
		bool execute_problems = false;
		run_benchmark(file_paths, planning_agent, output_file, execute_problems);
	}

	void run_coin_flip_benchmark(const std::string& folder, size_t start_index, size_t end_index)
	{
		std::string planning_agent = "a0";
		std::vector<std::string> file_paths;
		std::string output_file = "../Benchmarks/Benchmarks_coin_flip.csv";

		for (size_t i = start_index; i <= end_index; ++i)
		{
			file_paths.push_back(folder + "Coin_Flip_" + std::to_string(i) + ".maepl");
		}
		bool execute_problems = false;
		run_benchmark(file_paths, planning_agent, output_file, execute_problems);
	}

	void run_single_benchmark(const std::string& file, const std::string& planning_agent)
	{
		std::string output_file = get_benchmark_file_name();
		bool execute_problems = true;
		run_benchmark({ file }, planning_agent, output_file, execute_problems);
	}
}