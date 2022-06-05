#pragma once


#include <Windows.h>
#include <string>
#include <vector>
#include <memory>
#include "Configuration/json.hpp"
#include "ITask.h"

// A struct to keep the previous data of the file if it exists already.
// Using it, the rollback will be perfect.
struct PreviousRegistryData
{
	bool did_exist;
	std::wstring data;
};

/**
 * Represents an installation of a registry key.
 * Given an existing key, and a value, it copies the value into the given key.
 */
class RegistryInstallerTask : public ITask
{
public:
	RegistryInstallerTask(const std::wstring& registry_key_path, const std::wstring& registry_value_name, const std::wstring& registry_value);

	// Executing of the installation: Copying the value to a registry key.
	void execute() override;

	// Rolling-back the installation: Returning to the previous state
	// (previous value OR deleting the existing new key, depending on the previous state)
	void rollback() override;

	friend void from_json(const nlohmann::json& json_configuration, std::shared_ptr<RegistryInstallerTask>& task);

private:
	// In case the registry key already existed before the installation, this method will recover its data
	void recover_previous_registry_value(HKEY main_key, const std::wstring& sub_key) const;

	std::wstring registry_key_path;
	std::wstring registry_value_name;
	std::wstring registry_value;
	PreviousRegistryData previous_data;
};