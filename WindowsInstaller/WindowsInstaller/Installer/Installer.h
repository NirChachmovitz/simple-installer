#pragma once


#include <vector>
#include <memory>
#include <stack>

#include "Configuration/json.hpp"
#include "InstallerTask/ITask.h"

/**
 * Represents the RAII Windows Installer!
 */
class Installer
{
public:

	Installer();

	// A destructor meant to execute the rollback for each of the tasks which mistakenly occoured.
	~Installer();

	void install();

	void commit();

	friend void from_json(const nlohmann::json& j, Installer& installer);

private:
	// Tasks to be executed
	std::vector<std::shared_ptr<ITask>> tasks;

	bool is_committed;

	// Tasks which were executed, in case of a failure and a need to rollback
	std::stack<std::shared_ptr<ITask>> history;
};