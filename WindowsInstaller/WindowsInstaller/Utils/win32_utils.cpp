#include "win32_utils.h"

#include "exceptions.h"

HANDLE win32_utils::create_file(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition,
	uint32_t flags_and_attributes)
{
	HANDLE file_handle = CreateFileW(file_path.data(), desired_access, 0, nullptr, creation_disposition, flags_and_attributes, nullptr);
	if (INVALID_HANDLE_VALUE == file_handle) {
		throw CreateFileException("create_file failed, last error is: " + GetLastError());
	}
	return file_handle;
}


int win32_utils::get_file_size(HANDLE file_handle)
{
	uint32_t file_size = GetFileSize(file_handle, nullptr);
	if (INVALID_FILE_SIZE == file_size) {
		throw GetFileSizeException("get_file_size failed, last error is: " + GetLastError());
	}
	return file_size;
}


void win32_utils::copy_file(const std::wstring& file_path, const std::wstring& target_directory, bool fail_if_exists)
{
	std::wstring file_name = file_path.substr(file_path.find_last_of(L"/\\") + 1);
	std::wstring new_file_path = target_directory + file_name;

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

	return std::move(buffer);
}



void win32_utils::close_handle(HANDLE file_handle)
{
	if (0 == CloseHandle(file_handle)) {
		throw CloseHandleException("close_handle failed, last error is: " + GetLastError());
	}
}
