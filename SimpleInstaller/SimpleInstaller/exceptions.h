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

// File Exceptions
DEFINE_EXCEPTION(FileException, Win32UtilsException);
DEFINE_EXCEPTION(CreateFileException, FileException);
DEFINE_EXCEPTION(GetFileSizeException, FileException);
DEFINE_EXCEPTION(CopyFileException, FileException);
DEFINE_EXCEPTION(ReadFileException, FileException);
DEFINE_EXCEPTION(WriteFileException, FileException);
DEFINE_EXCEPTION(DeleteFileException, FileException);
DEFINE_EXCEPTION(PathCombineException, FileException);
DEFINE_EXCEPTION(CloseHandleException, FileException);
DEFINE_EXCEPTION(CreateDirectoryException, FileException);
DEFINE_EXCEPTION(RemoveDirectoryException, FileException);

// Registry Exceptions
DEFINE_EXCEPTION(RegistryException, Win32UtilsException);
DEFINE_EXCEPTION(RegCreateKeyException, RegistryException);
DEFINE_EXCEPTION(RegistryKeyAlreadyExistsException, RegistryException);
DEFINE_EXCEPTION(RegCloseKeyException, RegistryException);
DEFINE_EXCEPTION(RegQueryKeyException, RegistryException);
DEFINE_EXCEPTION(RegSetValueException, RegistryException);
DEFINE_EXCEPTION(RegDeleteKeyException, RegistryException);
DEFINE_EXCEPTION(RegFlushKeyException, RegistryException);

// JSON Exceptions
DEFINE_EXCEPTION(JsonException, WindowsInstallerException)
DEFINE_EXCEPTION(InvalidTargetPathException, JsonException)
DEFINE_EXCEPTION(ParseConfigurationException, JsonException)
DEFINE_EXCEPTION(UnknownTaskException, ParseConfigurationException)
