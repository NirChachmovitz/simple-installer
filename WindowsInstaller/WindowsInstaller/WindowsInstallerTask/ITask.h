#pragma once


#include <memory>

#include "macros.h"
#include "Utils/json.hpp"

/**
 * A class for defining a general task to do.
 * Supplies two pure functions to be overriden : execute & rollback.
 */
class ITask
{
public:
	DEFAULT_INTERFACE_METHODS(ITask)

	virtual void execute() = 0;
	virtual void rollback() = 0;
};