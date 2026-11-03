// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/cfg/basic.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once

namespace ss::defs::cfg
{
struct Basic
{
    std::string game_name{};
    std::string engine_name{};
    u32 window_width{};
    u32 window_height{};
};
} // namespace ss::defs::cfg