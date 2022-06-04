#pragma once


#include <string>
#include "ITask.h"

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

	void execute() override;
	void rollback() override;

	friend void from_json(const nlohmann::json& j, std::unique_ptr<FileInstallerTask>& task);

private:
	std::wstring source_file_path;
	std::wstring target_directory_path;
};