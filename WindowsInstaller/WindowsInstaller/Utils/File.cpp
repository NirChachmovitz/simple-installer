#include "File.h"

#include "win32_utils.h"


File::File(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition, uint32_t flags_and_attributes) :
			file_handle(win32_utils::create_file(file_path, desired_access, creation_disposition, flags_and_attributes))
{}

File::~File()
{
	win32_utils::close_handle(file_handle);
}
