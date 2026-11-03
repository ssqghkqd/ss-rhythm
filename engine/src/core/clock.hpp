// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/clock.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <chrono>

#include "defs/type.hpp"

namespace ss::core
{
class Clock
{
  private:
    std::chrono::high_resolution_clock::time_point
        start_time_{}; // 程序启动的绝对时间
    std::chrono::high_resolution_clock::time_point last_frame_time_{};
    f64 dt_{ 0.0 };
    f64 t_{ 0.0 };

    u32 fps_{};
    std::chrono::high_resolution_clock::time_point last_fps_time_{};

  public:
    Clock() = default;
    ~Clock() = default;
    Clock(const Clock&) = delete;
    Clock(Clock&&) = delete;
    Clock& operator=(const Clock&) = delete;
    Clock& operator=(Clock&&) = delete;

    void start();
    void update();
    [[nodiscard]] f64 dt() const
    {
        return dt_;
    }
    [[nodiscard]] f64 t() const
    {
        return t_;
    }

  private:
    void update_fps(const std::chrono::high_resolution_clock::time_point& now);
};
} // namespace ss::core