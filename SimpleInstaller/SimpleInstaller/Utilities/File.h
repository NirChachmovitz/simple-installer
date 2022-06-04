#pragma once


#include <Windows.h>
#include <string>
#include <vector>

class File
{
public:

	/**
	 * @param[in] file_path - the path to the file
	 * @param[in] desired_access - the requested access to the file or device
	 * @param[in] creation_disposition - an action to take on a file or device that exists or does not exist
	 * @param[in] flags_and_attributes - the file or device attributes and flags
	 */
	File(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition, 
		uint32_t flags_and_attributes);

	/**
	 * @param[in] number_of_bytes - number of bytes to be read from the file
	 * @returns vector of bytes with the data
	 */
	std::vector<std::byte> read(uint32_t number_of_bytes) const;
	std::vector<std::byte> read_entire_file() const;

	/**
	 * @param[in] buffer - the buffer to be written to the file from the beginning
	 */
	void write(std::vector<std::byte> buffer) const;

	/**
	 * @param[in] new_file_path - the place to which copy the file
	 */
	void copy(std::wstring new_file_path) const;

	// Wiping and deleting the file, so nothing remains...
	void remove();
	void wipe() const;

	int get_file_size() const;

	~File();
private:
	std::wstring file_path;
	HANDLE file_handle;
};
