#pragma once

#include <string>
#include <time.h>

std::string get_date_stamp()
{
	time_t now = time(0);
	struct tm ltm;
#if _MSC_VER
	localtime_s(&ltm, &now);
#else
	ltm = *(localtime(&now));
#endif

	std::string output;
	bool first = true;
	for (const auto& entry : { ltm.tm_year - 100, ltm.tm_mon + 1, ltm.tm_mday, ltm.tm_hour, ltm.tm_min, ltm.tm_sec })
	{
		if (first)
		{
			first = false;
		}
		else
		{
			output += "-";
		}

		if (entry < 10)
		{
			output += "0";
		}
		output += std::to_string(entry);
	}
	return output;

}
std::string get_benchmark_file_name(std::string date_stamp)
{
	return "../Benchmarks/Benchmarks_" + date_stamp + ".csv";
}
std::string get_benchmark_file_name()
{
	return get_benchmark_file_name(get_date_stamp());
}