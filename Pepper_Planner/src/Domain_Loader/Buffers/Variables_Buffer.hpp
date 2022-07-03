#pragma once

#include <deque>
#include <vector>
#include <string>

namespace del
{
	class Variables_Buffer
	{
	public:
		void set(Variables_Buffer& other);
		void add(const std::string& variable);
		size_t size() const;
		std::vector<std::string> get();
		std::vector<std::string>::const_iterator begin() const;
		std::vector<std::string>::const_iterator end() const;
	private:
		std::vector<std::string> variables;
	};

}