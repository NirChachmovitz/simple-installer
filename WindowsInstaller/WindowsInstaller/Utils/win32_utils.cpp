#include "win32_utils.h"

#include <memory>
#include <Shlwapi.h>
#include "exceptions.h"

HANDLE win32_utils::create_file(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition,
	uint32_t flags_and_attributes)
{
	const HANDLE file_handle = CreateFileW(file_path.data(), desired_access, 0, nullptr, creation_disposition, flags_and_attributes, nullptr);
	if (INVALID_HANDLE_VALUE == file_handle) {
		throw CreateFileException("create_file failed, last error is: " + GetLastError());
	}
	return file_handle;
}


int win32_utils::get_file_size(HANDLE file_handle)
{
	const uint32_t file_size = GetFileSize(file_handle, nullptr);
	if (INVALID_FILE_SIZE == file_size) {
		throw GetFileSizeException("get_file_size failed, last error is: " + GetLastError());
	}
	return file_size;
}


void win32_utils::copy_file(const std::wstring& file_path, const std::wstring& new_file_path, bool fail_if_exists)
{
	if (!CopyFileW(file_path.data(), new_file_path.data(), fail_if_exists)) {
		throw CopyFileException("copy_file failed, last error is: " + GetLastError());
	}
}


std::vector<std::byte> win32_utils::read_file(HANDLE file_handle, uint32_t number_of_bytes_to_read)
{
	std::vector<std::byte> buffer(number_of_bytes_to_read);
	DWORD number_of_bytes_read;

	if (!ReadFile(file_handle, buffer.data(), number_of_bytes_to_read, &number_of_bytes_read, nullptr)) {
		throw ReadFileException("read_file failed, last error is: " + GetLastError());
	}

	return buffer;
}


void win32_utils::write_file(HANDLE file_handle, std::vector<std::byte> buffer)
{
	DWORD number_of_bytes_written;
	if (!WriteFile(file_handle, buffer.data(), buffer.size(), &number_of_bytes_written, nullptr)) {
		throw WriteFileException("write_file failed, last error is: " + GetLastError());
	}
}


void win32_utils::delete_file(const std::wstring& file_path)
{
	if (!DeleteFileW(file_path.c_str())) {
		throw DeleteFileException("delete_file failed, last error is: " + GetLastError());

	}
}


std::wstring win32_utils::path_combine(const std::wstring& first_path, const std::wstring& second_path)
{
	std::vector<wchar_t> buffer(first_path.size() + second_path.size() + 2);
	if (nullptr == PathCombineW(buffer.data(), first_path.c_str(), second_path.c_str())) {
		throw PathCombineException("path_combine failed, last error is: " + GetLastError());
	}
	return std::wstring(buffer.begin(), buffer.end());
}


void win32_utils::close_handle(HANDLE file_handle)
{
	if (!CloseHandle(file_handle)) {
		throw CloseHandleException("close_handle failed, last error is: " + GetLastError());
	}
}
