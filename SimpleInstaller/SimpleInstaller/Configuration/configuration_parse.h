#pragma once


#include <string>

#include "ExternalResources/json.hpp"

/**
 * Meant to parse the json configuration and create it given its path
 */
namespace configuration_parse
{
	nlohmann::json parse_configuration(const std::wstring& configuration_path);
}