#pragma once


#include <vector>
#include <memory>
#include <stack>

#include "Utils/json.hpp"
#include "WindowsInstallerTask/ITask.h"

/**
 * Represents the RAII Windows Installer!
 */
class WindowsInstaller
{
public:

	WindowsInstaller();

	// A destructor meant to execute the rollback for each of the tasks which mistakenly occoured.
	~WindowsInstaller();

	void install();

	void commit();

	friend void from_json(const nlohmann::json& j, WindowsInstaller& installer);

private:
	// Tasks to be executed
	std::vector<std::shared_ptr<ITask>> tasks;

	bool is_committed;

	// Tasks which were executed, in case of a failure and a need to rollback
	std::stack<std::shared_ptr<ITask>> history;
};