#pragma once


#include "ITask.h"
#include "Utils/json.hpp"
#include <memory>

void from_json(const nlohmann::json& j, std::shared_ptr<ITask>& task);