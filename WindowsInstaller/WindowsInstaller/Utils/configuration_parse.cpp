#include "configuration_parse.h"

#include "File.h"
#include <fstream> // TODO: REMOVE IT!

nlohmann::json configuration_parse::parse_configuration(const std::string& configuration_path)
{
	/*File configuration_file(configuration_path, GENERIC_ALL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	int file_size = configuration_file.get_file_size();

	auto file_content = configuration_file.read(file_size);*/

	std::ifstream json_input(configuration_path);

	nlohmann::json configuration;

	json_input >> configuration;

	return configuration;
}
