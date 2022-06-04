#pragma once


#include <string>
#include <vector>
#include "macros.h"

/**
 * An abstract class representing a simple file and its required methods
 */
class IFile
{
public:
	DEFAULT_INTERFACE_METHODS(IFile)

	virtual std::vector<std::byte> read(uint32_t number_of_bytes) const = 0;
	virtual void write(std::vector<std::byte> buffer) = 0;
	virtual void copy(std::wstring target_path) = 0;
	virtual void remove() = 0;
};