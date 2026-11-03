// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/log/log_marco.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#ifndef NDEBUG // debug情况
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#else
#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_INFO
#endif

#include "log.hpp"

#define LG_TRACE(...) SPDLOG_LOGGER_TRACE(ss::log::get_logger(), __VA_ARGS__)
#define LG_DEBUG(...) SPDLOG_LOGGER_DEBUG(ss::log::get_logger(), __VA_ARGS__)
#define LG_INFO(...) SPDLOG_LOGGER_INFO(ss::log::get_logger(), __VA_ARGS__)
#define LG_WARN(...) SPDLOG_LOGGER_WARN(ss::log::get_logger(), __VA_ARGS__)
#define LG_ERROR(...) SPDLOG_LOGGER_ERROR(ss::log::get_logger(), __VA_ARGS__)
#define LG_CRI(...) SPDLOG_LOGGER_CRITICAL(ss::log::get_logger(), __VA_ARGS__)