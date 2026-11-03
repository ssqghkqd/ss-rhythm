// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/app.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <string>

#include "defs/type.hpp"

namespace ss::core
{
class App
{
  private:
    rg r_{};
    bool init_failed_{ false };
    std::string error_infor_{};

    // if32 last_stat_time_{};

  public:
    App() = default;
    ~App() = default;
    App(const App&) = delete;
    App& operator=(const App&) = delete;
    App(App&&) = delete;
    App& operator=(App&&) = delete;

    void init();
    i32 run();
    void mainloop();

  private:
};

} // namespace ss::core