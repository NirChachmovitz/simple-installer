#include "FileInstallerTask.h"

#include "Utils/File.h"
#include "Utils/win32_utils.h"

FileInstallerTask::FileInstallerTask(const std::wstring& source_file_path, const std::wstring& target_directory_path)
	: source_file_path(source_file_path), target_directory_path(target_directory_path), previous_data({false, {}})
{}


void FileInstallerTask::execute()
{
	std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(L"/\\") + 1);

	std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name); // TODO: maybe filesystem::path?
	
	try {
		File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);

		// File Exists:
		previous_data.did_exist = true;
		previous_data.data = target_file.read_entire_file();

	} catch (...) {
		// File does not exists, so nothing to do
	}

	win32_utils::copy_file(source_file_path, new_file_path, false);

	// Log here

}

void FileInstallerTask::rollback()
{
	try {
		std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(L"/\\") + 1);
		std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name);

		if (previous_data.did_exist) {
			recover_previous_file(new_file_path);
		}
		else {
			win32_utils::delete_file(new_file_path);
		}
	} catch (...) {
		throw;
	}
}

void FileInstallerTask::recover_previous_file(const std::wstring& new_file_path)
{
	File previous_file(new_file_path, GENERIC_ALL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	previous_file.write(previous_data.data);
}

// TODO: refactor
void from_json(const nlohmann::json& j, std::shared_ptr<FileInstallerTask>& task)
{
	std::string source_file_path = j.at("source_file_path").get<std::string>();
	std::string target_directory_path = j.at("target_directory_path").get<std::string>();
	task = std::make_shared<FileInstallerTask>(std::wstring(source_file_path.begin(), source_file_path.end()),
		std::wstring(target_directory_path.begin(), target_directory_path.end()));
}

