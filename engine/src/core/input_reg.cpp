// SPDX-License-Identifier: GPL-3.0-or-later
//
// engine/src/core/input_reg.cpp
// Copyright (C) 2025-2026 ss
//

#include "core/input_reg.hpp"
#include "defs/event/input_state.hpp"
#include "defs/event/window.hpp"
#include "defs/input/key_code.hpp"
namespace ss::core::input
{
InputRegister::InputRegister(rg& r) : r_(r)
{
    auto& dp = r_.ctx().get<entt::dispatcher>();

    dp.sink<defs::events::InputStateEvent>()
        .connect<&InputRegister::handle_input>(this);
}

void InputRegister::handle_input(const defs::events::InputStateEvent& event)
{
    auto& dp = r_.ctx().get<entt::dispatcher>();

    if (event.key_state[sc<size_t>(::ss::defs::KeyCode::ESC)])
    {
        dp.trigger(defs::events::WindowClose{});
    }

    last_state_ = event;
}
} // namespace ss::core::input