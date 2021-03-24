#pragma once
namespace del {
	void run_mapf_benchmark(const std::string& folder);
	void run_mapf_and_solve(const std::string& folder);
	void run_coin_flip_benchmark(const std::string& folder);
	void run_benchmark(const std::string& folder, const std::string& base_file_name, size_t start_index, size_t end_index);
}