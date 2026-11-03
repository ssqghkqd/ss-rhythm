// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/clock.cpp
// Copyright (C) 2025-2026 ss
//

#include "clock.hpp"
#include "defs/constant.hpp"
#include "utils/log/log_marco.hpp"
#include <chrono>

namespace ss::core
{
using GameClock = std::chrono::high_resolution_clock;
using Seconds = std::chrono::seconds;

void Clock::start()
{
    start_time_ = GameClock::now();
}

void Clock::update()
{
    const auto now = GameClock::now();
    dt_ = std::chrono::duration_cast<Seconds>(now - last_frame_time_).count();
    t_ = std::chrono::duration_cast<Seconds>(now - start_time_).count();
    last_frame_time_ = now;

    update_fps(now);
}

void Clock::update_fps(const GameClock::time_point& now)
{
    // 编译器会优化掉这里的 会删除掉这个函数 不在意
    if constexpr (!defs::state::IS_DEBUG)
    {
        return;
    }
    if (std::chrono::duration_cast<Seconds>(now - last_fps_time_).count()
        >= 1.0f)
    {
        LG_DEBUG("fps: {}", fps_);
        fps_ = 0;
        last_fps_time_ = now;
    }
    else
    {
        fps_++;
    }
}

} // namespace ss::core