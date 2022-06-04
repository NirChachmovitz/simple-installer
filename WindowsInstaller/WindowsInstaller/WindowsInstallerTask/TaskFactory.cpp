#include "TaskFactory.h"

#include "FileInstallerTask.h"

// TODO: refactor!
void from_json(const nlohmann::json& j, std::unique_ptr<ITask>& task)
{
	auto type = j.at("type").get<std::string>();
	//j.erase(j.find("type"));
	if ("FileCopyTask" == type)
	{
		//auto file_copy_task = j.get<FileCopyTask>();
		//task = std::make_unique<FileCopyTask>(file_copy_task);
		task = j.get<std::unique_ptr<FileInstallerTask>>();
	}

}