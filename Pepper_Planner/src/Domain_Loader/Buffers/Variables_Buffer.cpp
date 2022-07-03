#include "Variables_Buffer.hpp"

namespace del
{

	void Variables_Buffer::set(Variables_Buffer& other)
	{
		variables = other.get();
	}

	std::vector<std::string> Variables_Buffer::get()
	{
		std::vector<std::string> temp = std::move(variables);
		variables = {};
		return temp;
	}

	size_t Variables_Buffer::size() const
	{
		return variables.size();
	}

	std::vector<std::string>::const_iterator Variables_Buffer::begin() const
	{
		return variables.begin();
	}
	
	std::vector<std::string>::const_iterator Variables_Buffer::end() const
	{
		return variables.end();
	}

	void Variables_Buffer::add(const std::string& variable)
	{
		variables.push_back(variable);
	}
}