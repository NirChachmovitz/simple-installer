#include "configuration_parse.h"

#include <fstream> // TODO: try and do it without

nlohmann::json configuration_parse::parse_configuration(const std::wstring& configuration_path)
{
	/*File configuration_file(configuration_path, GENERIC_ALL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	int file_size = configuration_file.get_file_size();

	auto file_content = configuration_file.read(file_size);

	nlohmann::json configuration(file_content);*/

	std::ifstream json_input(configuration_path);

	nlohmann::json configuration;

	json_input >> configuration;

	return configuration;
}
