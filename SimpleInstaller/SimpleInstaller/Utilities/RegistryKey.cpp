#include "RegistryKey.h"

#include "Environment/win32_utils.h"

RegistryKey::RegistryKey(HKEY key, std::wstring sub_key, uint32_t option) :
	key(win32_utils::create_registry_key(key, sub_key, option))
{}


RegistryKey::~RegistryKey()
{
	win32_utils::close_registry_key(key);
}


std::vector<std::byte> read()
{
	
}
