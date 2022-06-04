#pragma once


#include <string>
#include <vector>
#include <memory>
#include "Configuration/json.hpp"
#include "ITask.h"

// A struct to keep the previous data of the file if it exists already.
// Using it, the rollback will be perfect.
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
	FileInstallerTask(const std::wstring& source_file_path, const std::wstring& target_directory_path);

	// Executing of the installation: Copying the file to a target directory.
	void execute() override;

	// Rolling-back the installation: Returning to the previous state
	// (previous file OR deleting the existing, depending on the previous state)
	void rollback() override;

	friend void from_json(const nlohmann::json& json_configuration, std::shared_ptr<FileInstallerTask>& task);

private:
	// In case the file already existed before the installation, this method will recover its data
	void recover_previous_file(const std::wstring& new_file_path) const;

	std::wstring source_file_path;
	std::wstring target_directory_path;
	PreviousData previous_data;
};