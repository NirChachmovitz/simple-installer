#include "RegistryInstallerTask.h"

#include "consts.h"
#include "ExternalResources/json.hpp"
#include "ExternalResources/Logger/easylogging++.h"
#include "Environment/win32.h"
#include "Utilities/RegistryKey.h"

std::unordered_map<std::wstring, HKEY> string_to_registry_key {
	{L"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
	{L"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
	{L"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
	{L"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
	{L"HKEY_USERS", HKEY_USERS}
};


RegistryInstallerTask::RegistryInstallerTask(const std::wstring& registry_key_path, const std::wstring& registry_value_name, const std::wstring& registry_value)
	: m_registry_key_path(registry_key_path), m_registry_value_name(registry_value_name), m_registry_value(registry_value), m_previous_data({ false, {} })
{}


HKEY convert_string_to_main_hkey(const std::wstring& key)
{
	const auto first_separator_position = key.find(LR"(\)");
	const auto main_key = key.substr(0, first_separator_position);
	return string_to_registry_key[main_key];
}


std::wstring convert_string_to_sub_key(const std::wstring& key)
{
	const auto first_separator_position = key.find(LR"(\)");
	return key.substr(first_separator_position + 1);
}


void RegistryInstallerTask::execute()
{
	LOG(INFO) << "Executing a registry installer task";

	const HKEY main_key = convert_string_to_main_hkey(m_registry_key_path);
	const std::wstring sub_key = convert_string_to_sub_key(m_registry_key_path);
	if (win32::is_registry_key_exists(main_key, sub_key)) {
		m_previous_data.did_exist = true;
	}

	const RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);

	if (m_previous_data.did_exist) {
		m_previous_data.data = registry_key.read(m_registry_value_name);
	}

	registry_key.write(m_registry_value_name, m_registry_value);
}

void RegistryInstallerTask::rollback()
{
	try {
		const HKEY main_key = convert_string_to_main_hkey(m_registry_key_path);
		const std::wstring sub_key = convert_string_to_sub_key(m_registry_key_path);

		if (m_previous_data.did_exist) {
			LOG(INFO) << "RegistryInstallerTask: Registry key already existed, recovering the previous data";
			recover_previous_registry_value(main_key, sub_key);
		}
		else {
			LOG(INFO) << "RegistryInstallerTask: Registry key did not exist previously, deleting it";
			const RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);
			registry_key.remove();
		}
	}
	catch (...) {
		LOG(ERROR) << "FileInstallerTask: Failed to rollback";
	}
}

void RegistryInstallerTask::recover_previous_registry_value(HKEY main_key, const std::wstring& sub_key) const
{
	const RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);

	registry_key.write(m_registry_value_name, m_previous_data.data);
}


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<RegistryInstallerTask>& task)
{
	std::string registry_key_path = json_configuration.at(REGISTRY_KEY_PATH_KEY).get<std::string>();
	std::string registry_value_name = json_configuration.at(REGISTRY_VALUE_NAME_KEY).get<std::string>();
	std::string registry_value = json_configuration.at(REGISTRY_VALUE_KEY).get<std::string>();

	task = std::make_shared<RegistryInstallerTask>(std::wstring(registry_key_path.begin(), registry_key_path.end()),
		std::wstring(registry_value_name.begin(), registry_value_name.end()),
		std::wstring(registry_value.begin(), registry_value.end()));
}

