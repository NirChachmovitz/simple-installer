#include "File.h"

#include "consts.h"
#include "Environment/win32.h"
#include "ExternalResources/Logger/easylogging++.h"


File::File(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition, uint32_t flags_and_attributes) :
			m_file_path(file_path), m_file_handle(win32::create_file(file_path, desired_access, creation_disposition, flags_and_attributes))
{}


File::File(File&& other) noexcept : m_file_path(other.m_file_path), m_file_handle(other.m_file_handle)
{
	other.m_file_handle = INVALID_HANDLE_VALUE;
}


File& File::operator=(File&& other)
{
	m_file_path = other.m_file_path;
	m_file_handle = other.m_file_handle;
	other.m_file_handle = INVALID_HANDLE_VALUE;
	return *this;
}


uint32_t File::get_file_size() const
{
	return win32::get_file_size(m_file_handle);
}


std::vector<std::byte> File::read(uint32_t number_of_bytes) const
{
	return win32::read_file(m_file_handle, number_of_bytes);
}


std::vector<std::byte> File::read_entire_file() const
{
	const auto file_size = get_file_size();
	return read(file_size);
}


void File::write(const std::vector<std::byte>& buffer) const
{
	win32::write_file(m_file_handle, buffer);
}



void File::copy(const std::wstring& new_file_path) const
{
	win32::copy_file(m_file_path, new_file_path, false);
}


void File::wipe() const
{
	const auto file_size = get_file_size();
	if (0 != file_size) {
		std::vector<std::byte> override_buffer(file_size, std::byte{NULL_CHAR});
		write(override_buffer);
	}

}


File::~File()
{
	try {
		if (INVALID_HANDLE_VALUE != m_file_handle) {
			win32::close_handle(m_file_handle);
		}
	} catch(...) {
		LOG(INFO) << "A debugger is present and the handle is not valid. Read the manual for more information";
	}
}
