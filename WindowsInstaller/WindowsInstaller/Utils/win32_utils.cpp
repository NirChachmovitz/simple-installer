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

void win32_utils::close_handle(HANDLE file_handle)
{
	if (0 == CloseHandle(file_handle)) {
		throw CloseHandleException("close_handle failed, last error is: " + GetLastError());
	}
}
