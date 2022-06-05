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

	std::vector<unsigned char> read(const std::wstring& value_name) const;

	/**
	 * @brief writes a string to the registry key
	 * @param[in] value_name - the name of the value to be written
	 * @param[in] value - the value to be written
	 */
	void write(const std::wstring& value_name, const std::wstring& value) const;

	void remove() const;

private:
	HKEY key;
};