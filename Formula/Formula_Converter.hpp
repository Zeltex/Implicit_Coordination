#pragma once

#include <string>

#include "Formula_Types.hpp"
namespace del {
	class Formula_Converter {
	public:
		static std::string type_to_string(Formula_Types type);
		static Formula_Types string_to_type(std::string type);
	private:
	};
}