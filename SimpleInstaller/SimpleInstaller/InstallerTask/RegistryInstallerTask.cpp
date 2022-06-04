#include "RegistryInstallerTask.h"

#include "consts.h"
#include "Configuration/json.hpp"
#include "Logger/easylogging++.h"
#include "Utilities/File.h"
#include "Environment/win32_utils.h"

RegistryInstallerTask::RegistryInstallerTask(const std::wstring& registry_key_path, const std::wstring& registry_value)
	: registry_key_path(registry_key_path), registry_value(registry_value), previous_data({ false, {} })
{}


void RegistryInstallerTask::execute()
{
	LOG(INFO) << "Executing a registry installer task";
	std::wstring file_name = source_file_path.substr(source_file_path.find_last_of(PATH_SEPARATOR) + 1);

	std::wstring new_file_path = win32_utils::path_combine(target_directory_path, file_name); // TODO: maybe filesystem::path?

	try {
		File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);

		// File Exists, so treat it accordingly and update the previous data structure
		previous_data.did_exist = true;
		previous_data.data = target_file.read_entire_file();

	}
	catch (...) {
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


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<RegistryInstallerTask>& task)
{
	std::string registry_key_path = json_configuration.at(REGISTRY_KEY_PATH_KEY).get<std::string>();
	std::string registry_value = json_configuration.at(REGISTRY_VALUE_KEY).get<std::string>();

	task = std::make_shared<RegistryInstallerTask>(std::wstring(registry_key_path.begin(), registry_key_path.end()),
		std::wstring(registry_value.begin(), registry_value.end()));
}

