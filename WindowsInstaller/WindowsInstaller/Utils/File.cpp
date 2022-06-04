#include "File.h"

#include "win32_utils.h"


File::File(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition, uint32_t flags_and_attributes) :
			file_path(file_path), file_handle(win32_utils::create_file(file_path, desired_access, creation_disposition, flags_and_attributes))
{}

int File::get_file_size()
{
	return win32_utils::get_file_size(file_handle);
}


std::vector<std::byte> File::read(int number_of_bytes)
{
	return win32_utils::read_file(file_handle, number_of_bytes);
}


void File::copy(std::wstring target_path)
{
	// TODO: handle the case where we overwrite existing file
	win32_utils::copy_file(file_path, target_path, true);
}


void File::remove()
{
	win32_utils::delete_file(file_path);
}

File::~File()
{
	win32_utils::close_handle(file_handle);
}
