#pragma once


#include <string>
#include "Utils/json.hpp"

namespace configuration_parse
{
	nlohmann::json parse_configuration(const std::string& configuration_path);
}