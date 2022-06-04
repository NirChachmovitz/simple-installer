#include "error_codes.h"
#include "consts.h"
#include "Utils/configuration_parse.h"


/**
 * @argv[1] - Path of the configuration file
 */
int wmain(int argc, wchar_t* argv[], wchar_t* envp[])
{
	// UNREFERENCED_PARAMETER(envp);
	if (VALID_NUMBER_OF_ARGUMENTS != argc) {
		return INVALID_NUMBER_OF_ARGUMENTS;
	}
	try {
		auto configuration = configuration_parse::parse_configuration(argv[1]);
	}
	catch (...) {
		
	}
	return INSTALLATION_SUCCESS;
}