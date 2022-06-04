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
	FileInstallerTask() = default;

	void execute() override;
	void rollback() override;

private:
	std::wstring source_file_path;
	std::wstring target_directory_path;
};