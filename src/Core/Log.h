#pragma once
#include "Core/Engine.h"
#include "Core/Logger.h"

#define HYDRA_INFO(...) Engine::GetLogger().Info(__VA_ARGS__)
#define HYDRA_ERROR(...) Engine::GetLogger().Error(__VA_ARGS__)
#define HYDRA_TRACE(...) Engine::GetLogger().Trace(__VA_ARGS__)
#define HYDRA_WARN(...) Engine::GetLogger().Warn(__VA_ARGS__)