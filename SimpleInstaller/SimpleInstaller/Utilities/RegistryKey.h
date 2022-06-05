#pragma once


#include <Windows.h>
#include <string>
#include <vector>


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

	/**
	 * @brief removes a registry key as part of the rollback
	 */
	void remove() const;

private:
	HKEY m_key;
};