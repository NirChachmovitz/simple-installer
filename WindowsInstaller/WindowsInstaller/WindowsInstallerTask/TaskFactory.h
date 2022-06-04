#pragma once


#include <memory>
#include "ITask.h"
#include "Utils/json.hpp"

/**
 * A factory for creating a specified task, according to the json file.
 */
void from_json(const nlohmann::json& json_configuration, std::shared_ptr<ITask>& task);