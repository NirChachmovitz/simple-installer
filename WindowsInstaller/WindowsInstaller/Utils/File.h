#pragma once


#include <Windows.h>
#include "IFile.h"

class File : public IFile
{
public:
	File(const std::wstring& file_path, uint32_t desired_access, uint32_t creation_disposition, 
		uint32_t flags_and_attributes);

	std::vector<std::byte> read(int number_of_bytes) override;
	void write(std::vector<std::byte> buffer) override;
	void copy(std::wstring new_file_path) override;
	void remove() override;

	int get_file_size();
	std::vector<std::byte> read_entire_file();
	void wipe();

	~File() override;
private:
	std::wstring file_path;
	HANDLE file_handle;
};