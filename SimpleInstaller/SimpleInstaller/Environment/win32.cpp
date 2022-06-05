#include "win32.h"

#include <memory>
#include <Shlwapi.h>

#include "consts.h"
#include "exceptions.h"

HANDLE win32::create_file(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition,
	uint32_t flags_and_attributes)
{
	const HANDLE file_handle = CreateFileW(file_path.data(), desired_access, 0, nullptr, creation_disposition, flags_and_attributes, nullptr);
	if (INVALID_HANDLE_VALUE == file_handle) {
		throw CreateFileException("create_file failed, last error is: " + GetLastError());
	}
	return file_handle;
}


int win32::get_file_size(HANDLE file_handle)
{
	const uint32_t file_size = GetFileSize(file_handle, nullptr);
	if (INVALID_FILE_SIZE == file_size) {
		throw GetFileSizeException("get_file_size failed, last error is: " + GetLastError());
	}
	return file_size;
}


void win32::copy_file(const std::wstring& file_path, const std::wstring& new_file_path, bool fail_if_exists)
{
	if (!CopyFileW(file_path.data(), new_file_path.data(), fail_if_exists)) {
		throw CopyFileException("copy_file failed, last error is: " + GetLastError());
	}
}


std::vector<std::byte> win32::read_file(HANDLE file_handle, uint32_t number_of_bytes_to_read)
{
	std::vector<std::byte> buffer(number_of_bytes_to_read);
	DWORD number_of_bytes_read;

	if (!ReadFile(file_handle, buffer.data(), number_of_bytes_to_read, &number_of_bytes_read, nullptr)) {
		throw ReadFileException("read_file failed, last error is: " + GetLastError());
	}

	return buffer;
}


void win32::write_file(HANDLE file_handle, std::vector<std::byte> buffer)
{
	DWORD number_of_bytes_written;
	if (!WriteFile(file_handle, buffer.data(), buffer.size(), &number_of_bytes_written, nullptr)) {
		throw WriteFileException("write_file failed, last error is: " + GetLastError());
	}
}


void win32::delete_file(const std::wstring& file_path)
{
	if (!DeleteFileW(file_path.c_str())) {
		throw DeleteFileException("delete_file failed, last error is: " + GetLastError());

	}
}


std::wstring win32::path_combine(const std::wstring& first_path, const std::wstring& second_path)
{
	std::vector<wchar_t> buffer(first_path.size() + second_path.size() + 2);
	if (nullptr == PathCombineW(buffer.data(), first_path.c_str(), second_path.c_str())) {
		throw PathCombineException("path_combine failed, last error is: " + GetLastError());
	}
	return std::wstring(buffer.begin(), buffer.end());
}


void win32::close_handle(HANDLE file_handle)
{
	if (!CloseHandle(file_handle)) {
		throw CloseHandleException("close_handle failed, last error is: " + GetLastError());
	}
}


HKEY win32::create_registry_key(HKEY key, std::wstring sub_key, uint32_t option)
{
	HKEY result;
	DWORD disposition;
	if (ERROR_SUCCESS != RegCreateKeyExW(key, sub_key.data(), 0, nullptr, option, KEY_ALL_ACCESS,
											nullptr, &result, &disposition)) {
		throw RegCreateKeyException("get_registry_key failed, last error is: " + GetLastError());
	}
	return result;
}


bool win32::is_registry_key_exists(HKEY key, std::wstring sub_key)
{
	HKEY result;
	if (ERROR_SUCCESS == RegOpenKeyExW(key, sub_key.data(), 0, KEY_ALL_ACCESS, &result)) {
		return true;
	}
	return false;
}


void win32::delete_registry_key(HKEY key, std::wstring sub_key)
{
	if (ERROR_SUCCESS != RegDeleteKey(key, sub_key.data())) {
		throw RegDeleteKeyException("delete_registry_key failed, last error is: " + GetLastError());
	}
}



void win32::close_registry_key(HKEY key)
{
	if (ERROR_SUCCESS != RegCloseKey(key)) {
		throw RegCloseKeyException("close_registry_key failed, last error is: " + GetLastError());
	}
}


std::vector<std::byte> win32::query_registry_value(HKEY key)
{
	UNREFERENCED_PARAMETER(key);
	return {};
/*	std::vector<unsigned char> data(TOTAL_BYTES_TO_READ_FROM_REGISTRY);
	DWORD data_size = TOTAL_BYTES_TO_READ_FROM_REGISTRY;
	if (ERROR_SUCCESS != RegQueryValueExW(key, nullptr, nullptr, nullptr, data.data(), &data_size)) {
		throw RegQueryKeyException("query_registry_value failed, last error is: " + GetLastError());
	}
	return std::vector<std::byte>(data.begin(), data.end());*/
}


void win32::set_registry_string_value(HKEY key, std::vector<std::byte> value)
{
	UNREFERENCED_PARAMETER(key);
	UNREFERENCED_PARAMETER(value);
	/*std::vector<unsigned char> byte_value(value.begin(), value.end());
	if (ERROR_SUCCESS != RegSetValueExW(key, nullptr, 0, REG_SZ, byte_value.data(), value.size())) {
		throw RegSetValueException("set_registry_string_value failed, last error is: " + GetLastError());
	}*/
}
