#include "WindowsInstaller.h"

#include "Utils/easylogging++.h"
#include "Utils/win32_utils.h"
#include "WindowsInstallerTask/TaskFactory.h"

WindowsInstaller::WindowsInstaller() : is_committed(false)
{}

void WindowsInstaller::install()
{
	// If thrown, main will destruct Installer
	for (const auto& task : tasks) {
		history.push(task);

		LOG(INFO) << "Executing task";
		task->execute();
		LOG(INFO) << "Executed task successfully";
	}
}

void WindowsInstaller::commit()
{
	is_committed = true;
}

WindowsInstaller::~WindowsInstaller()
{
	if (!is_committed) {
		while (!history.empty()) {
			try {
				auto current_task = history.top();
				history.pop(); // TODO: think. is this throwing? or anything else here.

				LOG(INFO) << "Rolling back task";
				current_task->rollback();
				LOG(INFO) << "Rolled back task successfully";
			} catch (...) {}
		}
	}
}


void from_json(const nlohmann::json& j, WindowsInstaller& installer)
{
	installer.tasks = j.at("tasks").get<std::vector<std::shared_ptr<ITask>>>();
}