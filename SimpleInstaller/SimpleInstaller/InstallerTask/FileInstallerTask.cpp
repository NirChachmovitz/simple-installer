#include "FileInstallerTask.h"

#include "consts.h"
#include "Configuration/json.hpp"
#include "Logger/easylogging++.h"
#include "Utilities/File.h"
#include "Environment/win32_utils.h"

FileInstallerTask::FileInstallerTask(const std::wstring& source_file_path, const std::wstring& target_directory_path)
	: source_file_path(source_file_path), target_directory_path(target_directory_path), previous_data({false, {}})
{}


void FileInstallerTask::execute()
{
	LOG(INFO) << "Executing a file installer task";
	std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(PATH_SEPARATOR) + 1);

	std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name); // TODO: maybe filesystem::path?
	
	try {
		File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);

		// File Exists, so treat it accordingly and update the previous data structure
		previous_data.did_exist = true;
		previous_data.data = target_file.read_entire_file();

	} catch (...) {
		// File does not exists, so nothing to do
	}

	win32_utils::copy_file(source_file_path, new_file_path, false);
}

void FileInstallerTask::rollback()
{
	try {
		std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(PATH_SEPARATOR) + 1);
		std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name);

		if (previous_data.did_exist) {
			LOG(INFO) << "FileInstallerTask: File already existed, recovering the previous data";
			recover_previous_file(new_file_path);
		}
		else {
			LOG(INFO) << "FileInstallerTask: File did not exist previously, wiping and deleting the file";
			File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
			target_file.remove();
		}
	}
	catch (...) {}
}

void FileInstallerTask::recover_previous_file(const std::wstring& new_file_path) const
{
	File previous_file(new_file_path, GENERIC_ALL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	previous_file.write(previous_data.data);
}


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<FileInstallerTask>& task)
{
	std::string source_file_path = json_configuration.at(SOURCE_FILE_PATH_KEY).get<std::string>();
	std::string target_directory_path = json_configuration.at(TARGET_DIRECTORY_PATH_KEY).get<std::string>();

	task = std::make_shared<FileInstallerTask>(std::wstring(source_file_path.begin(), source_file_path.end()),
												std::wstring(target_directory_path.begin(), target_directory_path.end()));
}

