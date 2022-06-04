#include "FileInstallerTask.h"

#include "Utils/File.h"
#include "Utils/win32_utils.h"

FileInstallerTask::FileInstallerTask(std::wstring source_file_path, std::wstring target_directory_path)
	: source_file_path(source_file_path), target_directory_path(target_directory_path)
{}


void FileInstallerTask::execute()
{
	//File file_to_install(source_file_path, GENERIC_ALL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	//file_to_install.copy(target_directory_path);

	// TODO: make sure.. is that okay? 
	win32_utils::copy_file(source_file_path, target_directory_path, true);

	// Log here

}

void FileInstallerTask::rollback()
{
	try {
		std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(L"/\\") + 2);
		std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name);
		win32_utils::delete_file(new_file_path);
	} catch (...) {
		throw;
	}
}

// TODO: refactor
void from_json(const nlohmann::json& j, std::shared_ptr<FileInstallerTask>& task)
{
	std::string source_file_path = j.at("source_file_path").get<std::string>();
	std::string target_directory_path = j.at("target_directory_path").get<std::string>();
	task = std::make_shared<FileInstallerTask>(std::wstring(source_file_path.begin(), source_file_path.end()),
		std::wstring(target_directory_path.begin(), target_directory_path.end()));
	//task->source_file_path = std::wstring(source_file_path.begin(), source_file_path.end());
	//task->target_directory_path = std::wstring(target_directory_path.begin(), target_directory_path.end());
}

