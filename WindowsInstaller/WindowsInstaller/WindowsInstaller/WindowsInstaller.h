#pragma once


#include <vector>
#include <memory>
#include <stack>
#include <string>

#include "WindowsInstallerTask/ITask.h"

class WindowsInstaller
{
public:
	WindowsInstaller();

private:
	std::vector<std::unique_ptr<ITask>> tasks;
	bool is_committed;
	std::stack<std::unique_ptr<ITask>> history;
};