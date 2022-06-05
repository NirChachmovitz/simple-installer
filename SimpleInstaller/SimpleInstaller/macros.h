#pragma once


#define DEFAULT_COPY_METHODS(classname) classname(const classname&) = default; \
										classname& operator=(const classname&) = default;

#define DEFAULT_MOVE_METHODS(classname) classname(classname&&) = default; \
										classname& operator=(classname&&) = default;

#define DEFAULT_COPY_AND_MOVE_METHODS(classname) DEFAULT_COPY_METHODS(classname) \
												 DEFAULT_MOVE_METHODS(classname)

#define DEFAULT_INTERFACE_METHODS(classname) classname() = default; \
											 virtual ~classname() = default; \
											 DEFAULT_COPY_AND_MOVE_METHODS(classname)

#define DEFAULT_CLASS_METHODS(classname) DEFAULT_COPY_AND_MOVE_METHODS(classname)