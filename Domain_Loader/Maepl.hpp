#pragma once

#include "Domain_Interface.hpp"
#include "Domain_Buffer.hpp"

namespace del {
    void parse_domain(Domain_Interface* domain, Domain_Buffer* buffer, FILE* file_in);
}
