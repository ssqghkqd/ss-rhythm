// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/utils/scope_timer.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <chrono>
#include <string>
#include <utility>

#include "utils/log/log_marco.hpp"

class ScopeTimer
{
  private:
    std::string name_{};
    std::chrono::time_point<std::chrono::high_resolution_clock> start_{};

  public:
    ScopeTimer(const ScopeTimer&) = delete;
    ScopeTimer(ScopeTimer&&) = delete;
    ScopeTimer& operator=(const ScopeTimer&) = delete;
    ScopeTimer& operator=(ScopeTimer&&) = delete;

    explicit ScopeTimer(std::string name)
        : name_(std::move(name)),
          start_(std::chrono::high_resolution_clock::now())
    {
    }

    ~ScopeTimer()
    {
        const auto end = std::chrono::high_resolution_clock::now();
        const auto duration
            = std::chrono::duration_cast<std::chrono::microseconds>(
                end - start_
            );
        SSLOG_DEBUG("{}: {}us", name_, duration.count());
    }

  private:
};