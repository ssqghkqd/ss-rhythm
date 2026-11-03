// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/render/platform_data.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

#include "defs/type.hpp"

namespace ss::defs::render
{
enum class WindowType : u8
{
    WAYLAND,
    X11,
    WIN32,
    COCOA, // macos

    OTHER,
};

struct PlatformData
{
    WindowType type{ WindowType::OTHER };
    void* native_window_handle{};
    void* native_display_type{};
};
} // namespace ss::defs::render