#include "RegistryInstallerTask.h"

#include "consts.h"
#include "Configuration/json.hpp"
#include "Logger/easylogging++.h"
#include "Environment/win32_utils.h"
#include "Utilities/RegistryKey.h"

std::unordered_map<std::wstring, HKEY> string_to_registry_key = {
	{L"HKEY_CLASSES_ROOT", HKEY_CLASSES_ROOT},
	{L"HKEY_CURRENT_CONFIG", HKEY_CURRENT_CONFIG},
	{L"HKEY_CURRENT_USER", HKEY_CURRENT_USER},
	{L"HKEY_LOCAL_MACHINE", HKEY_LOCAL_MACHINE},
	{L"HKEY_USERS", HKEY_USERS}
};

RegistryInstallerTask::RegistryInstallerTask(const std::wstring& registry_key_path, const std::wstring& registry_value)
	: registry_key_path(registry_key_path), registry_value(registry_value), previous_data({ false, {} })
{}

HKEY convert_string_to_main_hkey(const std::wstring& key)
{
	auto main_key = key.substr(0, key.find(PATH_SEPARATOR));
	return string_to_registry_key[main_key];
}

std::wstring convert_string_to_sub_hkey(const std::wstring& key)
{
	return key.substr(key.find(PATH_SEPARATOR) + 1);
}


void RegistryInstallerTask::execute()
{
	LOG(INFO) << "Executing a registry installer task";

	HKEY main_key = convert_string_to_main_hkey(registry_key_path);
	std::wstring sub_key = convert_string_to_sub_hkey(registry_key_path);
	if (win32_utils::is_registry_key_exists(main_key, sub_key)) {
		previous_data.did_exist = true;
	}

	RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);

	if (previous_data.did_exist) {
		previous_data.data = registry_key.read();
	}

	//std::vector<std::byte> bytes_value(registry_value.begin(), registry_value.end());
	//registry_key.write(bytes_value);
}

void RegistryInstallerTask::rollback()
{
	try {
		HKEY main_key = convert_string_to_main_hkey(registry_key_path);
		std::wstring sub_key = convert_string_to_sub_hkey(registry_key_path);

		if (previous_data.did_exist) {
			LOG(INFO) << "RegistryInstallerTask: Registry key already existed, recovering the previous data";
			recover_previous_registry_value(main_key, sub_key);
		}
		else {
			LOG(INFO) << "RegistryInstallerTask: Registry key did not exist previously, deleting it";
			RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);
			registry_key.remove();
		}
	}
	catch (...) {}
}

void RegistryInstallerTask::recover_previous_registry_value(HKEY main_key, const std::wstring& sub_key) const
{
	RegistryKey registry_key(main_key, sub_key, REG_OPTION_NON_VOLATILE);

	//registry_key.write(previous_data.data);
}


void from_json(const nlohmann::json& json_configuration, std::shared_ptr<RegistryInstallerTask>& task)
{
	std::string registry_key_path = json_configuration.at(REGISTRY_KEY_PATH_KEY).get<std::string>();
	std::string registry_value = json_configuration.at(REGISTRY_VALUE_KEY).get<std::string>();

	task = std::make_shared<RegistryInstallerTask>(std::wstring(registry_key_path.begin(), registry_key_path.end()),
		std::wstring(registry_value.begin(), registry_value.end()));
}

