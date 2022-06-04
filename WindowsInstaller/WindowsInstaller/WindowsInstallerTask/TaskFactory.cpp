#include "TaskFactory.h"

#include "FileInstallerTask.h"
#include "consts.h"

// TODO: refactor!
void from_json(const nlohmann::json& json_configuration, std::shared_ptr<ITask>& task)
{
	auto type = json_configuration.at(TYPE_KEY).get<std::string>();
	if ("FileInstallerTask" == type)
	{
		task = json_configuration.get<std::shared_ptr<FileInstallerTask>>();
	}

}