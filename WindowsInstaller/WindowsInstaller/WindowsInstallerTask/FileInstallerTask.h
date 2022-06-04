#pragma once


#include <string>
#include "ITask.h"

// A struct to keep the previous data of the file if it exists already, so the rollback will be perfect.
struct PreviousData
{
	bool did_exist;
	std::vector<std::byte> data;
};

/**
 * Represents an installation of a file.
 * Given an existing file, and a target directory, it copies the file into the given directory.
 */
class FileInstallerTask : public ITask
{
public:
	// TODO: add support for file already exists
	// TODO: add constructor?
	FileInstallerTask() = default;
	FileInstallerTask(const std::wstring& source_file_path, const std::wstring& target_directory_path);

	void execute() override;
	void rollback() override;

	friend void from_json(const nlohmann::json& j, std::shared_ptr<FileInstallerTask>& task);

private:
	void recover_previous_file(const std::wstring& new_file_path);

	std::wstring source_file_path;
	std::wstring target_directory_path;
	PreviousData previous_data;
};