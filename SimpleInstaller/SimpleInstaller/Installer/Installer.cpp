#include "Installer.h"

#include "Logger/easylogging++.h"
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
	// If thrown, main will destruct Installer
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
				m_history.pop(); // TODO: think. is this throwing? or anything else here.

				LOG(INFO) << "Rolling back task";
				current_task->rollback();
				LOG(INFO) << "Rolled back task successfully";
			}
			catch (...) {}
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