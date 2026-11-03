// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/defs/event/input_state.hpp
// Copyright (C) 2025-2026 ss
//

#pragma once
#include <bitset>

#include "defs/input/key_code.hpp"

namespace ss::defs::events
{
struct InputStateEvent
{
    // 键盘
    std::bitset<KeyCount> key_state{};

    // 鼠标
    std::bitset<ButtonCount> button_state{};
};
} // namespace ss::defs::events