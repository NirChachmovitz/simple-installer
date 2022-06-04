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

void FileInstallerTask::rollback()
{
	try {
		
	} catch (...) {
		throw;
	}
}

// TODO: refactor
void from_json(const nlohmann::json& j, std::shared_ptr<FileInstallerTask>& task)
{
	task = std::make_unique<FileInstallerTask>();
	task->source_file_path = j.at("source_file_path").get<std::string>();
	task->target_directory_path = j.at("target_directory_path").get<std::string>();
}

