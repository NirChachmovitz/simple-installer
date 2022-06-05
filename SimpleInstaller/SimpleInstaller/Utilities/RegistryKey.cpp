#include "RegistryKey.h"

#include "Environment/win32.h"


RegistryKey::RegistryKey(HKEY key, std::wstring sub_key, uint32_t option) :
	m_key(win32::create_registry_key(key, sub_key, option))
{}


RegistryKey::~RegistryKey()
{
	win32::close_registry_key(m_key);
}


std::wstring RegistryKey::read(const std::wstring& value_name) const
{
	return win32::query_registry_value(m_key, value_name);
}


void RegistryKey::write(const std::wstring& value_name, const std::wstring& value) const
{
	win32::set_registry_string_value(m_key, value_name, value);
	win32::flush_registry_key(m_key);
}
