// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/app.cpp
// Copyright (C) 2025-2026 ss
//

#include "core/app.hpp"

#include "defs/type.hpp"

#include "utils/log/log_marco.hpp"

#include "core/clock.hpp"
#include "core/init.hpp"
#include "core/window.hpp"

#include "render/renderer.hpp"

namespace ss::core
{
void App::init()
{
    const auto e = init::init(r_);
    if (!e.has_value())
    {
        error_infor_ = e.error().what();
        init_failed_ = true;
        return;
    }
}

i32 App::run()
{
    if (init_failed_)
    {
        LG_CRI("致命错误 退出程序:{}", error_infor_);
        return 1;
    }
    LG_DEBUG("游戏开始");
    mainloop();
    return 0;
}

void App::mainloop()
{
    auto& window = r_.ctx().get<Window>();
    auto& clock = r_.ctx().get<Clock>();
    auto& render = r_.ctx().get<render::Renderer>();

    clock.start();

    while (!window.is_should_close())
    {
        clock.update();

        render.render();
        render.frame();

        window.poll_events();
    }
}
} // namespace ss::core