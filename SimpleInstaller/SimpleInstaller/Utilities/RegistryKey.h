#pragma once


#include <Windows.h>
#include <string>
#include <vector>

#include "macros.h"


// A RAII class for guarding a registry key
class RegistryKey
{
public:
	RegistryKey(HKEY key, std::wstring sub_key, uint32_t option);

	~RegistryKey();

	/**
	 * @brief reads a string from a registry key and an according value name
	 * @param[in] value_name - a name of the value to be read
	 * @returns the string
	 */
	std::wstring read(const std::wstring& value_name) const;

	/**
	 * @brief writes a string to the registry key
	 * @param[in] value_name - the name of the value to be written
	 * @param[in] value - the value to be written
	 */
	void write(const std::wstring& value_name, const std::wstring& value) const;

	DELETED_COPY_METHODS(RegistryKey)

	RegistryKey(RegistryKey&& other) noexcept;

	RegistryKey& operator=(RegistryKey&& other);


private:
	HKEY m_key;
};