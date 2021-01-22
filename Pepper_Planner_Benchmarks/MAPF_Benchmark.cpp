#include "Run_Planner.hpp"
#include <chrono>
#include "DEL_Interface.hpp"


using namespace del;
void run_mapf_benchmark() {
	std::string planning_agent = "a0";
	std::vector<long> times;

	//std::string file_name = "../Examples/MAPF/p4.maepl";
	//DEL_Interface del_interface(file_name);
	//auto time_start = std::chrono::high_resolution_clock::now();
	//del_interface.create_policy(planning_agent);
	//auto time_end = std::chrono::high_resolution_clock::now();

	//times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count());
	//std::cout << "P4 took ms " << times.back() << std::endl;

	for (size_t i = 13; i <= 15; ++i) {
		std::string file_name = "../Examples/MAPF/p" + std::to_string(i) + ".maepl";
		DEL_Interface del_interface(file_name);
		auto time_start = std::chrono::high_resolution_clock::now();
		del_interface.create_policy(planning_agent, true);
		auto time_end = std::chrono::high_resolution_clock::now();

		times.push_back(std::chrono::duration_cast<std::chrono::milliseconds>(time_end - time_start).count());
		std::cout << "P" << i << " took ms " << times.back() << "\n\n";

		std::ofstream output;
		output.open("../Benchmarks/Benchmarks_mapfdu.csv");
		for (size_t j = 0; j < times.size(); ++j) {
			output << "P" << (j + 1) << ": " << times[j] << " ms\n";
		}
		output.close();

	}

	__debugbreak;
}