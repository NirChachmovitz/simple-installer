#include "TaskFactory.h"

#include "FileInstallerTask.h"
#include "consts.h"
#include "exceptions.h"

constexpr std::string_view FILE_INSTALLER_TASK_TYPE = "FileInstallerTask";


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<ITask>& task)
{
	auto type = json_configuration.at(TYPE_KEY).get<std::string>();
	if (FILE_INSTALLER_TASK_TYPE == type) {
		task = json_configuration.get<std::shared_ptr<FileInstallerTask>>();
	}
	else {
		throw UnknownTaskException();
	}

}