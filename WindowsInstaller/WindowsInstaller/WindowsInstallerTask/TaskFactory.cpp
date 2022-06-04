#include "TaskFactory.h"

#include "FileInstallerTask.h"

// TODO: refactor!
void from_json(const nlohmann::json& j, std::shared_ptr<ITask>& task)
{
	auto type = j.at("type").get<std::string>();
	//j.erase(j.find("type"));
	if ("FileInstallerTask" == type)
	{
		//auto file_copy_task = j.get<FileCopyTask>();
		//task = std::make_unique<FileCopyTask>(file_copy_task);
		task = j.get<std::shared_ptr<FileInstallerTask>>();
	}

}