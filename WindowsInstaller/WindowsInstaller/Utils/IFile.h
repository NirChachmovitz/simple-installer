#pragma once


#include <string>
#include <vector>
#include "macros.h"

class IFile
{
public:
	DEFAULT_INTERFACE_METHODS(IFile)

	virtual std::vector<char> read(int number_of_bytes) = 0;
	//virtual void write(std::vector<char> buffer) = 0;
	virtual void copy(std::string target_path) = 0;
	virtual void remove() = 0;
};