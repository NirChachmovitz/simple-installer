#pragma once


#include <Windows.h>
#include <string>
#include <vector>


namespace win32_utils
{
	HANDLE create_file(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition,
		uint32_t flags_and_attributes);

	int get_file_size(HANDLE file_handle);

	void copy_file(const std::wstring& file_path, const std::wstring& new_file_path, bool fail_if_exists);

	std::vector<std::byte> read_file(HANDLE file_handle, uint32_t number_of_bytes_to_read);

	void write_file(HANDLE file_handle, std::vector<std::byte> buffer);

	void delete_file(const std::wstring& file_path);

	std::wstring path_combine(const std::wstring& first_path, const std::wstring& second_path);

	void close_handle(HANDLE file_handle);

}
