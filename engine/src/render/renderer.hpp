// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/render/renderer.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include "defs/error.hpp"
#include "defs/type.hpp"

#include "defs/render/platform_data.hpp"

namespace ss::render
{
class Renderer
{
  private:
    u32 width_{};
    u32 height_{};

  public:
    Renderer() = default;
    ~Renderer() = default;
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;

    eperr<void> init(u32 width, u32 height, const defs::render::PlatformData& pd);

    void render();
    void frame();

  private:
};
} // namespace ss::render