// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/window.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include <SDL3/SDL_video.h>

#include "defs/error.hpp"
#include "defs/input/key_code.hpp"
#include "defs/render/platform_data.hpp"
#include "defs/type.hpp"

namespace ss::core
{
class Window
{
  private:
    rg& r_;
    SDL_Window* window_{};

    bool should_close_{ false };

  public:
    Window(rg& r);
    ~Window();
    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;
    Window(Window&&) = delete;
    Window& operator=(Window&&) = delete;

    eperr<void> init();
    eperr<void> create_window(u32 width, u32 height, cstr title);

    [[nodiscard]] bool is_should_close() const;
    void close_window();

    void poll_events();

    [[nodiscard]] eperr<ss::defs::render::PlatformData> get_platform_window_data() const;

  private:
    void broadcast_input() const;
};
} // namespace ss::core