#pragma once

#include "Domain_Interface.hpp"
#include "General_Domain.hpp"

namespace del {
    void parse_domain(Domain_Interface* domain, General_Domain* buffer, FILE* file_in);
}
