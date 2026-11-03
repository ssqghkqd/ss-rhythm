// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/init.cpp
// Copyright (C) 2025-2026 ss
//

#include "core/init.hpp"

#include "clock.hpp"
#include "core/input_reg.hpp"
#include "core/window.hpp"
#include "defs/constant.hpp"
#include "defs/error.hpp"
#include "defs/func.hpp"
#include "defs/render/platform_data.hpp"
#include "defs/type.hpp"
#include "render/renderer.hpp"
#include "resources/cfg_mag.hpp"

namespace ss::core::init
{
eperr<void> init(rg& r)
{
    fill_reg(r);

    TRY(load_config(r));

    init_basic(r);

    TRY(init_window(r));

    TRY(init_renderer(r));

    return {};
}

void fill_reg(rg& r)
{
    r.ctx().emplace<entt::dispatcher>();

    r.ctx().emplace<Window>(r);
    r.ctx().emplace<render::Renderer>();
    r.ctx().emplace<Clock>();
    r.ctx().emplace<input::InputRegister>(r);

    r.ctx().emplace<res::CfgMag>();
}

eperr<void> load_config(rg& r)
{
    auto& cfgm = r.ctx().get<res::CfgMag>();
    TRY(cfgm.load_basic(defs::reference::cfg_basic_path));
    return {};
}

eperr<void> init_renderer(rg& r)
{
    auto& render = r.ctx().get<render::Renderer>();
    auto& window = r.ctx().get<Window>();

    const auto basic = r.ctx().get<res::CfgMag>().get_basic();

    const auto pd = TRY(window.get_platform_window_data());

    TRY(render.init(basic.window_width, basic.window_height, pd));
    return {};
}

void init_basic(rg& r)
{
    auto& clock = r.ctx().get<Clock>();
    clock.start();
}

eperr<void> init_window(rg& r)
{
    auto& window = r.ctx().get<Window>();

    const auto basic = r.ctx().get<res::CfgMag>().get_basic();

    TRY(window.init());
    TRY(window.create_window(basic.window_width, basic.window_height, basic.game_name.c_str()));

    return {};
}

} // namespace ss::core::init