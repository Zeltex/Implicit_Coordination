#pragma once

#include <string>
#include <vector>

namespace del {
	void run_mapf_benchmark(const std::string& folder, size_t start_index, size_t end_index);
	void run_benchmark(const std::vector<std::string>& file_paths, const std::string& planning_agent, const std::string& output_file, bool execute_problems);
	void run_coin_flip_benchmark(const std::string& folder, size_t start_index, size_t end_index);
	void run_single_benchmark(const std::string& file, const std::string& planning_agent);
}