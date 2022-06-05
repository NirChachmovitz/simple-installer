#include "RegistryKey.h"

#include "Environment/win32.h"


RegistryKey::RegistryKey(HKEY key, std::wstring sub_key, uint32_t option) :
	key(win32::create_registry_key(key, sub_key, option))
{}


RegistryKey::~RegistryKey()
{
	win32::close_registry_key(key);
}


std::vector<std::byte> RegistryKey::read() const
{
	return win32::query_registry_value(key);
}


void RegistryKey::write(const std::vector<std::byte>& value) const
{
	win32::set_registry_string_value(key, value);
}


void RegistryKey::remove() const
{
	// TODO: maybe do nullptr everywhere?
	win32::delete_registry_key(key, nullptr);
}
