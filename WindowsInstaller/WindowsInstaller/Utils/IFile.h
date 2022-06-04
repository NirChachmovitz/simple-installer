#pragma once


#include <string>
#include <vector>
#include "macros.h"

class IFile
{
public:
	DEFAULT_INTERFACE_METHODS(IFile)

	virtual std::vector<std::byte> read() = 0;
	virtual void write(std::vector<std::byte> buffer) = 0;
	virtual void copy(std::wstring target_path) = 0;
	virtual void remove() = 0;
};