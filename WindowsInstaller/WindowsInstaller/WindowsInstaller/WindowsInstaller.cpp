#include "WindowsInstaller.h"

#include "Utils/win32_utils.h"
#include "WindowsInstallerTask/TaskFactory.h"

WindowsInstaller::WindowsInstaller() : is_committed(false)
{}

void from_json(const nlohmann::json& j, WindowsInstaller& installer)
{
	installer.tasks = j.at("tasks").get<std::vector<std::unique_ptr<ITask>>>();
}