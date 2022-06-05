#include "Installer.h"

#include "ExternalResources/Logger/easylogging++.h"
#include "Environment/win32.h"
#include "InstallerTask/TaskFactory.h"

Installer::Installer() : m_is_committed(false)
{}


void Installer::commit()
{
	m_is_committed = true;
}


void Installer::install()
{
	// If thrown, main will destruct Installer, and rollback all tasks
	for (const auto& task : m_tasks) {
		m_history.push(task);

		LOG(INFO) << "Executing task";
		task->execute();
		LOG(INFO) << "Executed task successfully";
	}

	// Reaching here meaning great success!
	commit();
}


void Installer::rollback()
{
	if (!m_is_committed) {
		while (!m_history.empty()) {
			try {
				const auto current_task = m_history.top();
				m_history.pop();

				LOG(INFO) << "Rolling back task";
				current_task->rollback();
				LOG(INFO) << "Rolled back task successfully";
			}
			catch (...) {
				LOG(INFO) << "Couldn't rollback current task, last error: " << std::to_string(GetLastError());
			}
		}
	}
}


Installer::~Installer()
{
	rollback();
}


void from_json(const nlohmann::json& j, Installer& installer)
{
	installer.m_tasks = j.at("tasks").get<std::vector<std::shared_ptr<ITask>>>();
}