#include "Misc.hpp"

namespace del {
	std::string get_indentation(size_t indentation) {
		return (indentation > 0 ? "-" + get_indentation(indentation - 1) : "");
	}
}