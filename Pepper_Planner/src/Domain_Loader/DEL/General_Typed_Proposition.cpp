#include "General_Typed_Propositions.hpp"
#include "Inputs_Buffer.hpp"

namespace del
{
	General_Typed_Proposition::General_Typed_Proposition(const std::string& name, std::vector<std::string> type_inputs)
		:name(name), type_inputs(type_inputs)
	{

	}
	
	void General_Typed_Propositions::add(const std::string& name, Inputs_Buffer& inputs_buffer)
	{
		Inputs inputs = inputs_buffer.get();
		std::vector<std::string> types;
		for (size_t i = 0; i < inputs.size(); ++i)
		{
			const Input& input = inputs.get(i);
			types.push_back(input.get_type());
		}

		propositions.insert({ name, types});
	}
	std::set<General_Typed_Proposition>::const_iterator General_Typed_Propositions::begin() const
	{
		return propositions.begin();
	}
	std::set<General_Typed_Proposition>::const_iterator General_Typed_Propositions::end() const
	{
		return propositions.end();
	}
}