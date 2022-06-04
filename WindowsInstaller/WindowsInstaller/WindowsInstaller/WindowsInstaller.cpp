#include "WindowsInstaller.h"

#include "Utils/win32_utils.h"
#include "WindowsInstallerTask/TaskFactory.h"

WindowsInstaller::WindowsInstaller() : is_committed(false)
{}

void WindowsInstaller::install()
{
	// If thrown, main will destruct Installer
	for (const auto& task : tasks) {
		history.push(task);

		// LOG

		task->execute();
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
				current_task->rollback();
			} catch (...) {}
		}
	}
}


void from_json(const nlohmann::json& j, WindowsInstaller& installer)
{
	installer.tasks = j.at("tasks").get<std::vector<std::shared_ptr<ITask>>>();
}