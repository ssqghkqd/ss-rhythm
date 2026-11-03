// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/log/log.cpp
// Copyright (C) 2025-2026 ss
//

#include "log.hpp"

#include "defs/constant.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>
namespace ss::log
{
sptr<spdlog::logger> get_logger()
{
    static sptr<spdlog::logger> logger = []()
    {
        // 控制台彩色输出
        auto sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        sink->set_pattern("[%H:%M:%S][%^%l%$][%s:%# %!]: %v");

        auto lg = std::make_shared<spdlog::logger>("ss", sink);
        if constexpr (defs::state::IS_DEBUG)
        {
            lg->set_level(spdlog::level::trace);
        }
        else
        {
            lg->set_level(spdlog::level::info);
        }

        SPDLOG_LOGGER_INFO(lg, "日志设置完成");

        return lg;
    }();

    return logger;
}
} // namespace ss::log