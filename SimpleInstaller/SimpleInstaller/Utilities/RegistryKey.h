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

	std::vector<std::byte> read() const;

	void write(std::vector<std::byte>);

private:
	HKEY key;
};