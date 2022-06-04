#pragma once


#include <string>
#include <Windows.h>


namespace win32_utils
{
	HANDLE create_file(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition,
		uint32_t flags_and_attributes);

	void close_handle(HANDLE file_handle);
}
