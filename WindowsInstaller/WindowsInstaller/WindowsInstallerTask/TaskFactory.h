#pragma once


#include "ITask.h"
#include "Utils/json.hpp"
#include <memory>

void from_json(const nlohmann::json& j, std::unique_ptr<ITask>& task);