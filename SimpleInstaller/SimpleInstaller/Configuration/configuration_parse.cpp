#include "configuration_parse.h"

#include <fstream> 

nlohmann::json configuration_parse::parse_configuration(const std::wstring& configuration_path)
{
	std::ifstream json_input(configuration_path);

	nlohmann::json configuration;

	json_input >> configuration;

	return configuration;
}
