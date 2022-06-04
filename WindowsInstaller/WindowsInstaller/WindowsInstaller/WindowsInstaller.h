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
	~WindowsInstaller();

	void install();

	void commit();

	friend void from_json(const nlohmann::json& j, WindowsInstaller& installer);

private:
	std::vector<std::shared_ptr<ITask>> tasks;
	bool is_committed;
	std::stack<std::shared_ptr<ITask>> history;
};