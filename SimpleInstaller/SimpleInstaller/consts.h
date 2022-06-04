#pragma once


#include <string>

constexpr int VALID_NUMBER_OF_ARGUMENTS = 2;

constexpr char NULL_CHAR = '\0';

constexpr std::string_view TYPE_KEY = "type";
constexpr std::string_view SOURCE_FILE_PATH_KEY = "source_file_path";
constexpr std::string_view TARGET_DIRECTORY_PATH_KEY = "target_directory_path";
constexpr std::string_view REGISTRY_KEY_PATH_KEY = "registry_key_path";
constexpr std::string_view REGISTRY_VALUE_KEY = "registry_value";
constexpr std::wstring_view PATH_SEPARATOR = L"/\\";