#pragma once


#include <vector>
#include <memory>
#include <stack>

#include "Utils/json.hpp"
#include "WindowsInstallerTask/ITask.h"

class WindowsInstaller
{
public:
	WindowsInstaller();

	friend void from_json(const nlohmann::json& j, WindowsInstaller& installer);

private:
	std::vector<std::unique_ptr<ITask>> tasks;
	bool is_committed;
	std::stack<std::unique_ptr<ITask>> history;
};