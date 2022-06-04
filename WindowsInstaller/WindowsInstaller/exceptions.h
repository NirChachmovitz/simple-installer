#pragma once


#include <stdexcept>

#define DEFINE_EXCEPTION(exception_name, exception_base) \
	class exception_name : public exception_base { \
		public: \
			exception_name(const std::string& error_string = "") : exception_base(error_string) {} \
	};

DEFINE_EXCEPTION(WindowsInstallerException, std::runtime_error);

// Windows32 Exceptions
DEFINE_EXCEPTION(Win32UtilsException, WindowsInstallerException);
DEFINE_EXCEPTION(FileException, Win32UtilsException);
DEFINE_EXCEPTION(CreateFileException, FileException);
DEFINE_EXCEPTION(GetFileSizeException, FileException);
DEFINE_EXCEPTION(CopyFileException, FileException);
DEFINE_EXCEPTION(ReadFileException, FileException);
DEFINE_EXCEPTION(CloseHandleException, FileException);