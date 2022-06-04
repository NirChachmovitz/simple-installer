#include "FileInstallerTask.h"

#include "Utils/File.h"

void FileInstallerTask::execute()
{
	try {
		File file_to_install(source_file_path, GENERIC_ALL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);

		file_to_install.copy(target_directory_path);

		// Log here
	} catch (...) {
		throw;
	}
}
