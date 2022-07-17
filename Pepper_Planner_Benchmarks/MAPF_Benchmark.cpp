#include "Run_Planner.hpp"
#include <chrono>
#include "DEL_Interface.hpp"
#include "Utils.h"


namespace del {
	void run_mapf_benchmark(const std::string& folder, size_t start_index, size_t end_index) {
		std::string planning_agent = "a0";
		std::vector<long long> times;

		for (size_t i = start_index; i <= end_index; ++i) {
			std::string file_name = folder + "p" + std::to_string(i) + ".maepl";
			DEL_Interface del_interface(file_name);
			auto time_start = std::chrono::high_resolution_clock::now();
			bool solved = del_interface.create_policy(planning_agent, true);
			auto time_end = std::chrono::high_resolution_clock::now();

			times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count());
			std::cout << "P" << i << " took ms " << times.back() << ", solved = " << solved << std::endl << std::endl;

			std::ofstream output;
			output.open("../Benchmarks/Benchmarks_mapfdu.csv");
			for (size_t j = 0; j < times.size(); ++j) {
				output << "P" << (j + 1) << ": " << times[j] << " ms" << std::endl;
			}
			output.close();

		}
	}

	void run_benchmark(const std::string& file, const std::string& planning_agent)
	{
		std::string benchmark_file_name = get_benchmark_file_name();
		DEL_Interface del_interface(file);
		auto time_start = std::chrono::high_resolution_clock::now();
		bool solved = del_interface.create_policy(planning_agent, false);
		auto time_end = std::chrono::high_resolution_clock::now();

		auto time = std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count();
		std::string out_string = file + " took ms " + std::to_string(time) + " (including policy extraction), solved = " + (solved ? "true" : "false") + "\n";
		bool failed = false;
		size_t iterations = 0;
		while (!del_interface.is_solved() && !failed && iterations++ < 100)
		{
			const Action* action = del_interface.get_next_action();
			if (action != nullptr)
			{
				out_string += action->to_string() + "\n";
				if (!del_interface.perform_action(action))
				{
					out_string += "Action is inapplicable\n";
					failed = true;
				}
			}
			else
			{
				out_string +=  "No applicable action\n";
				failed = true;
			}
		}

		if (failed)
		{
			out_string += "Failed to perform actions from policy\n";
		}
		std::cout << out_string;

		std::ofstream output;
		output.open(benchmark_file_name);
		output << out_string;
		output.close();

	}
}