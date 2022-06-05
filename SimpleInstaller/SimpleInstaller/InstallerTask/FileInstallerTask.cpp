#include "FileInstallerTask.h"

#include "consts.h"
#include "ExternalResources/json.hpp"
#include "ExternalResources/Logger/easylogging++.h"
#include "Utilities/File.h"
#include "Environment/win32.h"

FileInstallerTask::FileInstallerTask(const std::wstring& source_file_path, const std::wstring& target_directory_path)
	: m_source_file_path(source_file_path), m_target_directory_path(target_directory_path), m_previous_data({false, {}})
{}


void FileInstallerTask::execute()
{
	LOG(INFO) << "Executing a file installer task";
	const std::wstring file_name = m_source_file_path.substr(m_source_file_path.find_last_of(PATH_SEPARATOR) + 1);

	const std::wstring new_file_path = win32::path_combine(m_target_directory_path, file_name); // TODO: maybe filesystem::path?
	
	try {
		const File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);

		// File Exists, so treat it accordingly and update the previous data structure
		m_previous_data.did_exist = true;
		m_previous_data.data = target_file.read_entire_file();

	} catch (...) {
		LOG(INFO) << "FileInstallerTask: File did not exist before";
	}

	win32::copy_file(m_source_file_path, new_file_path, false);
}

void FileInstallerTask::rollback()
{
	try {
		const std::wstring file_name = m_source_file_path.substr(m_source_file_path.find_last_of(PATH_SEPARATOR) + 1);
		const std::wstring new_file_path = win32::path_combine(m_target_directory_path, file_name);

		if (m_previous_data.did_exist) {
			LOG(INFO) << "FileInstallerTask: File already existed, recovering the previous data";
			recover_previous_file(new_file_path);
		}
		else {
			LOG(INFO) << "FileInstallerTask: File did not exist previously, wiping and deleting the file";
			const File target_file(new_file_path, GENERIC_ALL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL);
			target_file.remove();
		}
	}
	catch (...) {
		LOG(ERROR) << "FileInstallerTask: Failed to rollback";
	}
}

void FileInstallerTask::recover_previous_file(const std::wstring& new_file_path) const
{
	const File previous_file(new_file_path, GENERIC_ALL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL);

	previous_file.write(m_previous_data.data);
}


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<FileInstallerTask>& task)
{
	std::string source_file_path = json_configuration.at(SOURCE_FILE_PATH_KEY).get<std::string>();
	std::string target_directory_path = json_configuration.at(TARGET_DIRECTORY_PATH_KEY).get<std::string>();

	task = std::make_shared<FileInstallerTask>(std::wstring(source_file_path.begin(), source_file_path.end()),
												std::wstring(target_directory_path.begin(), target_directory_path.end()));
}

